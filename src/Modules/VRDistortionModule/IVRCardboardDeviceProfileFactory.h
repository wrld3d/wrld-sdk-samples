// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VRCardboardDeviceProfile.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
			class IVRCardboardDeviceProfileFactory
			{
			public:
				virtual ~IVRCardboardDeviceProfileFactory() { }
				virtual Eegeo::VR::Distortion::VRCardboardDeviceProfile* GetCardboardDeviceProfile() const = 0;
			};
        }
    }
}
