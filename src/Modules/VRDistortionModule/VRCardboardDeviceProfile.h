// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            struct VRScreen {
                float width;   // The long edge of the phone.
                float height;  // The short edge of the phone.
                float border;  // Distance from bottom of the cardboard to the bottom edge of screen.
            };
            
            struct VRLenses {
                float separation;     // Center to center.
                float offset;         // Offset of lens center from top or bottom of cardboard.
                float screenDistance; // Distance from lens center to the phone screen.
                
                int alignment;  // Determines whether lenses are placed relative to top, bottom or
                // center.  It is actually a signum (-1, 0, +1) relating the scale of
                // the offset's coordinates to the device coordinates.
                
                static const int AlignTop = -1;    // Offset is measured down from top of device.
                static const int AlignCenter = 0;  // Center alignment ignores offset, hence scale is zero.
                static const int AlignBottom = 1;  // Offset is measured up from bottom of device.
            };
            
            struct VRMaxFOV {
                float outer;  // Towards the side of the screen.
                float inner;  // Towards the center line of the screen.
                float upper;  // Towards the top of the screen.
                float lower;  // Towards the bottom of the screen.
            };
            
            struct VRDistortionCoeff {
                float k1;
                float k2;
            };
            
            struct VRDevice {
                VRLenses lenses;
                VRMaxFOV maxFOV;
                VRDistortionCoeff distortion;
                VRDistortionCoeff inverse;
            };
            
            class VRCardboardDeviceProfile
            {
            public:
                
                VRCardboardDeviceProfile();
                
                VRDistortionCoeff ApproximateInverse(VRDistortionCoeff distort, float maxRadius = 1, int numSamples = 10);
                void SetupProfile(float profileData[]);
                float Distort(float r, float k1, float k2);
                float DistortInv(float radius, float k1, float k2);
                void SolveLeastSquares(double **ppMatA, double vecY[], int numSamples, const int numCoefficients, double vecX[]);
                void GetLeftEyeVisibleScreenRect(float undistortedFrustum[], float *pRect);
                void GetLeftEyeVisibleTanAngles(float* pResult);
                void GetLeftEyeNoLensTanAngles(float* pResult);
                float GetVerticalLensOffset();
                Eegeo::v2 GetScreenMeshCenter(float width, float height);
                VRDevice GetDevice();
            private:
                VRDevice m_device;
                VRScreen m_screen;
            };
        }
    }
}

