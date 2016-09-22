// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VRCardboardDeviceProfile.h"
#include "IVRCardboardDeviceProfileFactory.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
			class VRCardboardV1ProfileFactory : public IVRCardboardDeviceProfileFactory
			{
			public:
				VRCardboardV1ProfileFactory();
				Eegeo::VR::Distortion::VRCardboardDeviceProfile* GetCardboardDeviceProfile() const;
			};
        }
    }
}
