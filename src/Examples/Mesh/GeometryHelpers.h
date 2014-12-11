// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include <vector>

namespace Examples
{
    namespace GeometryHelpers
    {
        struct Vertex
        {
            Eegeo::v3 position;
            Eegeo::v3 normal;
            Eegeo::v2 uv;
            
            Vertex()
            : position(Eegeo::v3::Zero())
            , normal(Eegeo::v3::Zero())
            , uv(Eegeo::v2::Zero())
            {
            }
            
            Vertex(const Eegeo::v3& position, const Eegeo::v3& normal, const Eegeo::v2 uv)
            : position(position)
            , normal(normal)
            , uv(uv)
            {
            }
        };
        
        void BuildBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices);
    }
}