// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VRCardboardDeviceProfile.h"
#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRCardboardDeviceProfile::VRCardboardDeviceProfile(){
                
                float profileData[] = {
                    50, //Outer
                    50, //Upper
                    50, //Inner
                    50, //Lower
                    0.12622245f, //Width
                    0.07031249f, //Height
                    0.003f, //Border
                    0.064f, //Separation
                    0.035f, //Offset
                    0.061f, //Screen Distance
                    VRLenses::AlignBottom, //Alignment
                    0.28f, //K1
                    0.49f  //K2
                };
                SetupProfile(profileData);
                
                EXAMPLE_LOG("Creating native profile for %.2f, %.2f, %.2f",m_device.maxFOV.outer, m_device.distortion.k1, m_device.distortion.k2);
            }
            
            VRDevice VRCardboardDeviceProfile::GetDevice() {
                return m_device;
            }
            
            float VRCardboardDeviceProfile::Distort(float r, float k1, float k2) {
                float r2 = r * r;
                return ((k2 * r2 + k1) * r2 + 1) * r;
            }
            
            float VRCardboardDeviceProfile::DistortInv(float radius, float k1, float k2) {
                // Secant method.
                float r0 = 0;
                float r1 = 1;
                float dr0 = radius - Distort(r0, k1, k2);
                while (Eegeo::Math::Abs(r1 - r0) > 0.0001f) { 
                    float dr1 = radius - Distort(r1, k1, k2);
                    float r2 = r1 - dr1 * ((r1 - r0) / (dr1 - dr0));
                    r0 = r1;
                    r1 = r2;
                    dr0 = dr1;
                }
                return r1;
            }
            
            void VRCardboardDeviceProfile::SetupProfile(float profileData[]) {
                m_device.maxFOV.outer = profileData[0];
                m_device.maxFOV.upper = profileData[1];
                m_device.maxFOV.inner = profileData[2];
                m_device.maxFOV.lower = profileData[3];
                m_screen.width = profileData[4];
                m_screen.height = profileData[5];
                m_screen.border = profileData[6];
                m_device.lenses.separation = profileData[7];
                m_device.lenses.offset = profileData[8];
                m_device.lenses.screenDistance = profileData[9];
                m_device.lenses.alignment = (int)profileData[10];
                m_device.distortion.k1 = profileData[11];
                m_device.distortion.k2 = profileData[12];
                m_device.inverse = ApproximateInverse(m_device.distortion);
            }
            
            VRDistortionCoeff VRCardboardDeviceProfile::ApproximateInverse(VRDistortionCoeff distort, float maxRadius, const int numSamples) {
                const int numCoefficients = 2;

                // R + k1*R^3 + k2*R^5 = r, with R = rp = distort(r)
                // Repeating for numSamples:
                //   [ R0^3, R0^5 ] * [ K1 ] = [ r0 - R0 ]
                //   [ R1^3, R1^5 ]   [ K2 ]   [ r1 - R1 ]
                //   [ R2^3, R2^5 ]            [ r2 - R2 ]
                //   [ etc... ]                [ etc... ]
                // That is:
                //   matA * [K1, K2] = y
                // Solve:
                //   [K1, K2] = inverse(transpose(matA) * matA) * transpose(matA) * y
                double **ppMatA = new double*[numSamples];
                double vecY[numSamples];
                for (int i = 0; i < numSamples; ++i) {
                    ppMatA[i] = new double[numCoefficients];
                    float r = maxRadius * (i + 1) / (float) numSamples;
                    double rp = Distort(r, distort.k1, distort.k2);
                    double v = rp;
                    for (int j = 0; j < numCoefficients; ++j) {
                        v *= rp * rp;
                        ppMatA[i][j] = v;
                    }
                    vecY[i] = r - rp;
                }
                double vecK[numCoefficients];
                SolveLeastSquares(ppMatA, vecY, numSamples, numCoefficients, vecK);
                VRDistortionCoeff coeef = {(float)vecK[0],(float)vecK[1]};
                for (int i = 0; i < numSamples; ++i) {
                    delete [] ppMatA[i];
                }
                
                delete [] ppMatA;
                return coeef;
            }
            
            void VRCardboardDeviceProfile::SolveLeastSquares(double **ppMatA, double vecY[], const int numSamples, const int numCoefficients, double vecX[]) {
                if (numCoefficients != 2) {
                    EXAMPLE_LOG("Only 2 coefficients supported.");
                    return;
                }
                // Calculate transpose(A) * A
                double matATA[numCoefficients][numCoefficients];

                
                for (int k = 0; k < numCoefficients; ++k) {
                    for (int j = 0; j < numCoefficients; ++j) {
                        double sum = 0.0f;
                        for (int i = 0; i < numSamples; ++i) {
                            sum += ppMatA[i][j] * ppMatA[i][k];
                        }
                        matATA[j][k] = sum;
                    }
                }

                // Calculate the inverse of transpose(A) * A.  Inverting isn't recommended for numerical
                // stability, but should be ok for small and well-behaved data sets.  Using manual matrix
                // inversion here (hence the restriction of numCoefficients to 2 in this function).

                double matInvATA[numCoefficients][numCoefficients];
                
                double det = matATA[0][0] * matATA[1][1] - matATA[0][1] * matATA[1][0];
                matInvATA[0][0] = matATA[1][1] / det;
                matInvATA[1][1] = matATA[0][0] / det;
                matInvATA[0][1] = -matATA[1][0] / det;
                matInvATA[1][0] = -matATA[0][1] / det;

                // Calculate transpose(A) * y
                double vecATY[numCoefficients];
                for (int j = 0; j < numCoefficients; ++j) {
                    double sum = 0.0;
                    for (int i = 0; i < numSamples; ++i) {
                        sum += ppMatA[i][j] * vecY[i];
                    }
                    vecATY[j] = sum;
                }

                // Now matrix multiply the previous values to get the result.
                for (int j = 0; j < numCoefficients; ++j) {
                    double sum = 0.0;
                    for (int i = 0; i < numCoefficients; ++i) {
                        sum += matInvATA[i][j] * vecATY[i];
                    }
                    vecX[j] = sum;
                }
            }
            
            /// The vertical offset of the lens centers from the screen center.
            float VRCardboardDeviceProfile::GetVerticalLensOffset() {
                    return (m_device.lenses.offset - m_screen.border - m_screen.height/2) * m_device.lenses.alignment;
            }
            
            /// Calculates the tan-angles from the maximum FOV for the left eye for the
            /// current device and screen parameters, assuming no lenses.
            void VRCardboardDeviceProfile::GetLeftEyeNoLensTanAngles(float* pResult) {
                // Tan-angles from the max FOV.
                float fovLeft = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-m_device.maxFOV.outer)), m_device.distortion.k1, m_device.distortion.k2);
                float fovTop = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(m_device.maxFOV.upper)), m_device.distortion.k1, m_device.distortion.k2);
                float fovRight = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(m_device.maxFOV.inner)), m_device.distortion.k1, m_device.distortion.k2);
                float fovBottom = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-m_device.maxFOV.lower)), m_device.distortion.k1, m_device.distortion.k2);
                // Viewport size.
                float halfWidth = m_screen.width / 4;
                float halfHeight = m_screen.height / 2;
                // Viewport center, measured from left lens position.
                float centerX = m_device.lenses.separation / 2 - halfWidth;
                float centerY = -GetVerticalLensOffset();
                float centerZ = m_device.lenses.screenDistance;
                // Tan-angles of the viewport edges, as seen through the lens.
                float screenLeft = (centerX - halfWidth) / centerZ;
                float screenTop = (centerY + halfHeight) / centerZ;
                float screenRight = (centerX + halfWidth) / centerZ;
                float screenBottom = (centerY - halfHeight) / centerZ;
                // Compare the two sets of tan-angles and take the value closer to zero on each side.
                pResult[0] = Eegeo::Max<float>(fovLeft, screenLeft);
                pResult[1] = Eegeo::Min<float>(fovTop, screenTop);
                pResult[2] = Eegeo::Min<float>(fovRight, screenRight);
                pResult[3] = Eegeo::Max<float>(fovBottom, screenBottom);
            }
            
            /// Calculates the tan-angles from the maximum FOV for the left eye for the
            /// current device and screen parameters.
            void VRCardboardDeviceProfile::GetLeftEyeVisibleTanAngles(float* pResult) {
                // Tan-angles from the max FOV.
                
                float fovLeft = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-m_device.maxFOV.outer));
                float fovTop = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(m_device.maxFOV.upper));
                float fovRight = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(m_device.maxFOV.inner));
                float fovBottom = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-m_device.maxFOV.lower));
                // Viewport size.
                float halfWidth = m_screen.width / 4;
                float halfHeight = m_screen.height / 2;
                // Viewport center, measured from left lens position.
                float centerX = m_device.lenses.separation / 2 - halfWidth;
                float centerY = -1 * GetVerticalLensOffset();
                float centerZ = m_device.lenses.screenDistance;
                // Tan-angles of the viewport edges, as seen through the lens.
                float screenLeft = Distort((centerX - halfWidth) / centerZ, m_device.distortion.k1, m_device.distortion.k2);
                float screenTop = Distort((centerY + halfHeight) / centerZ, m_device.distortion.k1, m_device.distortion.k2);
                float screenRight = Distort((centerX + halfWidth) / centerZ, m_device.distortion.k1, m_device.distortion.k2);
                float screenBottom = Distort((centerY - halfHeight) / centerZ, m_device.distortion.k1, m_device.distortion.k2);
                // Compare the two sets of tan-angles and take the value closer to zero on each side.

                pResult[0] = Eegeo::Max<float>(fovLeft, screenLeft);
                pResult[1] = Eegeo::Min<float>(fovTop, screenTop);
                pResult[2] = Eegeo::Min<float>(fovRight, screenRight);
                pResult[3] = Eegeo::Max<float>(fovBottom, screenBottom);
            }
            
            void VRCardboardDeviceProfile::GetLeftEyeVisibleScreenRect(float undistortedFrustum[], float *pRect) {
                float dist = m_device.lenses.screenDistance;
                float eyeX = (m_screen.width - m_device.lenses.separation) / 2;
                float eyeY = GetVerticalLensOffset() + m_screen.height / 2;
                float left = (undistortedFrustum[0] * dist + eyeX) / m_screen.width;
                float top = (undistortedFrustum[1] * dist + eyeY) / m_screen.height;
                float right = (undistortedFrustum[2] * dist + eyeX) / m_screen.width;
                float bottom = (undistortedFrustum[3] * dist + eyeY) / m_screen.height;
                
                pRect[0] = left;
                pRect[1] = bottom;
                pRect[2] = right - left;
                pRect[3] = top - bottom;
            }
            
            Eegeo::v2 VRCardboardDeviceProfile::GetScreenMeshCenter(float width, float height) {
                Eegeo::v2 screenCenter = Eegeo::v2(width/2.0f, height/2.0f);
                
                float offset = GetVerticalLensOffset() * (height);
                screenCenter.y -= offset;
                return screenCenter;
            }
        }
    }
}
