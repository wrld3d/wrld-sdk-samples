// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GeometryHelpers.h"
#include "Bounds.h"

namespace Examples
{
    namespace GeometryHelpers
    {
        void BuildBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices)
        {
            const int faces = 6;
            const int pointsPerFace = 4;
            out_vertices.clear();
            out_triangleIndices.clear();
            out_vertices.reserve(pointsPerFace*faces);
            out_triangleIndices.reserve(faces*3*2);
            
            Eegeo::v3 faceNormals[faces] =
            {
                Eegeo::v3(1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, 1.f),
                Eegeo::v3(-1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, -1.f),
                Eegeo::v3(0.f, 1.f, 0.f),
                Eegeo::v3(0.f, -1.f, 0.f)
            };
            
            Eegeo::v3 points[8] =
            {
                Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z),
                Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, halfDimensions.y, halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
            };
            
            int pointIndices[faces*pointsPerFace] =
            {
                1, 0, 3, 2,
                0, 4, 2, 6,
                4, 5, 6, 7,
                5, 1, 7, 3,
                4, 0, 5, 1,
                7, 3, 6, 2,
            };
            
            
            Eegeo::Geometry::Bounds2D uvRects[] =
            {
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.0f), Eegeo::v2(0.5f, 0.5f)),    // +ve x, "0"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.0f), Eegeo::v2(1.0f, 0.5f)),    // +ve z, "1"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.5f), Eegeo::v2(0.5f, 1.0f)),    // -ve x, "2"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.5f), Eegeo::v2(1.0f, 1.0f)),    // -ve z, "3"
                Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // +ve y (top)
                Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // -ve y (bottom)
            };
            
            
            for (int i = 0; i < 6; ++i)
            {
                const Eegeo::v3& faceNormal = faceNormals[i];
                
                const Eegeo::Geometry::Bounds2D& uvRect = uvRects[i];
                
                u16 offset = static_cast<u16>(i*pointsPerFace);
                out_vertices.push_back(Vertex(points[pointIndices[offset + 0]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 1]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 2]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 3]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                
                out_triangleIndices.push_back(offset + 0);
                out_triangleIndices.push_back(offset + 1);
                out_triangleIndices.push_back(offset + 2);
                out_triangleIndices.push_back(offset + 2);
                out_triangleIndices.push_back(offset + 1);
                out_triangleIndices.push_back(offset + 3);
            }
        }
    }
}