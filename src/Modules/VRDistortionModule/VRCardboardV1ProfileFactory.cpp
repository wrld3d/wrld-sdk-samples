// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCardboardV1ProfileFactory.h"
#include "Types.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
        	VRCardboardV1ProfileFactory::VRCardboardV1ProfileFactory()
			{

			}

			Eegeo::VR::Distortion::VRCardboardDeviceProfile* VRCardboardV1ProfileFactory:: GetCardboardDeviceProfile() const
			{
				const float profileData[13] =
				{
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
					Eegeo::VR::Distortion::VRLenses::AlignBottom, //Alignment
					0.28f, //K1
					0.49f  //K2
				};
				return Eegeo_NEW((Eegeo::VR::Distortion::VRCardboardDeviceProfile)(profileData));
			}
        }
    }
}
