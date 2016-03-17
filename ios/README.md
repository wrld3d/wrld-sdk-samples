<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo iOS Examples

## Requirements

- [Xcode](https://developer.apple.com/xcode/) (7.2 tested)
- [CMake](https://cmake.org/) (3.1.1  or higher)

## eeGeo API Key 

In order to use the eeGeo 3D Maps SDK, you must sign up for a free developer account at https://www.eegeo.com/developers. After signing up, you'll be able to create an [API key](https://www.eegeo.com/developers/apikeys) for your apps.

To run these examples, you must then place the API key in the [ViewController.mm](https://github.com/eegeo/mobile-sdk-harness/blob/master/ios/ios_src/ViewController.mm#L6) file.

## Setup

1.  In the root of the repo, run the command `./update.platform -p ios` to download the latest eeGeo iOS SDK.
	*	We recommend you run this step frequently to keep your SDK version up to date.
2.  In the `ios` directory, run `mkdir build` to create a build directory.
3.  In the `ios/build` directory, run `cmake -G Xcode ..` to generate a project file.
4.  Open the `SDKSamplesApp.xcodeproj` project file in Xcode.
5.	Ensure that you have set an eeGeo API key [as described above](#eegeo-api-key).
6.	Build and run the SDKSamplesApp target.

## C++03 Builds

By default, the above steps generate a project using C\+\+11. To build versions of the application which are C\+\+03 only, follow these steps:

1.  In the root of the repo, run the command `./update.platform -p ios -c` to download the latest C\+\+03 version of the eeGeo iOS SDK.
2.  In the `ios` directory, run `mkdir build` to create a build directory.
3.  In the `ios/build` directory, run `cmake -G Xcode -DCOMPILE_CPP_03=1 ..` to generate a project file.
4.  Open the `SDKSamplesApp.xcodeproj` project file in Xcode and run the application.

## Building from the command line

To build from the command line, you will need to install the Xcode Command Line Tools by running the command: `xcode-select --install`

Then run `./build.sh -p ios` from the root of this repository to build the project.

For C\+\+03 builds, run `./build.sh -p ios -c`.