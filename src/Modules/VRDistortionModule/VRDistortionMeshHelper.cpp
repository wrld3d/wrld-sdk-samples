// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VRDistortionMeshHelper.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            void ComputeMeshPoints(int width, int height, bool distortVertices,std::vector<Vertex>& vertices, int screenWidth, int screenHeight, VRCardboardDeviceProfile profile) {
                
                const float xScale = 2.0f;
                const float yScale = 2.0f;
                
                float lensFrustum[4];
                float noLensFrustum[4];
                
                float viewport[4];
                
                profile.GetLeftEyeVisibleTanAngles(lensFrustum);
                profile.GetLeftEyeNoLensTanAngles(noLensFrustum);
                profile.GetLeftEyeVisibleScreenRect(noLensFrustum, viewport);
                
                vertices.reserve(2 * width * height);
                
                for (int e = 0, vidx = 0; e < 2; e++) {
                    for (int j = 0; j < height; j++) {
                        for (int i = 0; i < width; i++, vidx++) {
                            double u = (float)i / (width - 1);
                            double v = (float)j / (height - 1);
                            double s, t;  // The texture coordinates in StereoScreen to read from.
                            if (distortVertices) {
                                // Grid points regularly spaced in StreoScreen, and barrel distorted in the mesh.
                                s = u;
                                t = v;
                                float x = Eegeo::Math::Lerp<float>(lensFrustum[0], lensFrustum[2], u);
                                //                            float x = Mathf.Lerp(lensFrustum[0], lensFrustum[2], u);
                                float y = Eegeo::Math::Lerp<float>(lensFrustum[3], lensFrustum[1], v);
                                float d = Eegeo::Math::Sqrtf(x * x + y * y);
                                float r = profile.DistortInv(d, profile.GetDevice().distortion.k1, profile.GetDevice().distortion.k2);
                                float p = x * r / d;
                                float q = y * r / d;
                                u = (p - noLensFrustum[0]) / (noLensFrustum[2] - noLensFrustum[0]);
                                v = (q - noLensFrustum[3]) / (noLensFrustum[1] - noLensFrustum[3]);
                            } else {
                                // Grid points regularly spaced in the mesh, and pincushion distorted in
                                // StereoScreen.
                                float p = Eegeo::Math::Lerp<float>(noLensFrustum[0], noLensFrustum[2], u);
                                float q = Eegeo::Math::Lerp<float>(noLensFrustum[3], noLensFrustum[1], v);
                                float r = Eegeo::Math::Sqrtf(p * p + q * q);
                                float d = profile.Distort(r, profile.GetDevice().distortion.k1, profile.GetDevice().distortion.k2);
                                float x = p * d / r;
                                float y = q * d / r;
                                s = Eegeo::Math::Clamp01((x - lensFrustum[0]) / (lensFrustum[2] - lensFrustum[0]));
                                t = Eegeo::Math::Clamp01((y - lensFrustum[3]) / (lensFrustum[1] - lensFrustum[3]));
                            }
                            // Convert u,v to mesh screen coordinates.
                            float aspect = screenWidth / screenHeight;
                            u = (viewport[0] + u * viewport[2] - 0.5f) * aspect * xScale;
                            v = (viewport[1] + v * viewport[3] - 0.5f ) * yScale;
                            s = (s + e) / 2;
                            vertices.push_back(Vertex(Eegeo::v3(u, v, 1), Eegeo::v3::Zero(), Eegeo::v2(s,t)));
                        }
                    }
                    
                    float w = lensFrustum[2] - lensFrustum[0];
                    lensFrustum[0] = -(w + lensFrustum[0]);
                    lensFrustum[2] = w - lensFrustum[2];
                    w = noLensFrustum[2] - noLensFrustum[0];
                    noLensFrustum[0] = -(w + noLensFrustum[0]);
                    noLensFrustum[2] = w - noLensFrustum[2];
                    viewport[0] = 1 - (viewport[0] + viewport[2]);
                }
            }
            
            void ComputeMeshIndices(int width, int height, bool distortVertices, std::vector<u16>& indices) {
                indices.reserve(2 * (width - 1) * (height - 1) * 6);
                int halfwidth = width / 2;
                int halfheight = height / 2;
                std::vector<u16>::iterator iidx = indices.begin();
                for (int e = 0, vidx = 0; e < 2; e++) {
                    for (int j = 0; j < height; j++) {
                        for (int i = 0; i < width; i++, vidx++) {
                            if (i == 0 || j == 0)
                                continue;
                            // Build a quad.  Lower right and upper left quadrants have quads with the triangle
                            // diagonal flipped to get the vignette to interpolate correctly.
                            if ((i <= halfwidth) == (j <= halfheight)) {
                                // Quad diagonal lower left to upper right.
                                //                            indices.insert(iidx++, vidx);
                                indices.insert(iidx++, vidx);
                                indices.insert(iidx++, vidx - width);
                                indices.insert(iidx++, vidx - width - 1);
                                indices.insert(iidx++, vidx - width - 1);
                                indices.insert(iidx++, vidx - 1);
                                indices.insert(iidx++, vidx);
                            } else {
                                // Quad diagonal upper left to lower right.
                                indices.insert(iidx++, vidx - 1);
                                indices.insert(iidx++, vidx);
                                indices.insert(iidx++, vidx - width);
                                indices.insert(iidx++, vidx - width);
                                indices.insert(iidx++, vidx - width - 1);
                                indices.insert(iidx++, vidx - 1);
                            }
                        }
                    }
                }
            }
            
            void BuildDistortionMesh(std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices, int screenWidth, int screenHeight, VRCardboardDeviceProfile profile) {
                out_vertices.clear();
                out_triangleIndices.clear();
                
                int kMeshWidth = 40, kMeshHeight = 40;
                bool kDistortVertices = true;
                ComputeMeshPoints(kMeshWidth, kMeshHeight, kDistortVertices, out_vertices, screenWidth, screenHeight, profile);
                ComputeMeshIndices(kMeshWidth, kMeshHeight, kDistortVertices, out_triangleIndices);
                
            }
        }
    }
}
