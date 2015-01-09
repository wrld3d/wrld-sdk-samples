// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__FileIOExample__
#define __ExampleApp__FileIOExample__

#include "GlobeCameraExampleBase.h"

#include "IFileIO.h"

namespace Examples
{
class FileIOExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Helpers::IFileIO& m_fileIO;

public:
	FileIOExample(Eegeo::Helpers::IFileIO& m_fileIO,
	              Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "FileIOExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt) {}
	void Draw() {}
	void Suspend() {}
    
    
};
}


#endif /* defined(__ExampleApp__FileIOExample__) */
