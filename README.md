eeGeo 3D Maps mobile-sdk-harness
================================

Additional documentation available at http://www.eegeo.com/developers/documentation/

iOS
===
> Requirements:  
\- [Xcode](https://developer.apple.com/xcode/) (version tested: 7.2)  
\- [CMake](https://cmake.org/) (>= 3.1.1)

* Run ./update.platform.sh -p ios to get the latest platform libraries and headers.
* Within the ios directory, create a build directory for your project
* Navigate to your build directory and generate the project with CMake: `cmake -G Xcode ..`  
This is an 'out of source' build - all of the objects and binaries will be built inside of this directory. The `..` denotes that we're generating from source in the parent (in this case 'ios') directory.
* Open the SDKSamplesApp.xcodeproj that CMake has generated
* The platform needs an API key to operate. Sign up at https://www.eegeo.com/developers/ to get your API key and introduce it into the following line in ViewController.mm : 
  const std::string API_KEY "OBTAIN API_KEY FROM https://www.eegeo.com/developers/ AND INSERT IT HERE".
* Scroll between the examples using the Next and Previous buttons; the current example name is displayed at the top of the screen.
* To build at the command line, run ./build -p ios from the repository root.

Android
=======
> Requirements:  
\- [Eclipse IDE for Java Developers](https://eclipse.org/downloads/)   
\- [Android Developer Tools](http://developer.android.com/tools/help/adt.html) (>= 22.6)  
\- [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) (>= r10d)

* Install the Android SDK and NDK
* Run ./update.platform.sh -p android to get the latest platform libraries and headers.
* Open an ADT Eclipse workspace, importing the cloned repository as an Android project
* Configure your workspace:
    * File -> Import -> Android: 'Existing Android Code Into Workspace'
    * Select the 'android' directory in the repository
    * ADT -> Preferences -> Android -> NDK : Set NDK location to the root of your NDK directory
    * Select imported activity -> Android Tools : 'Add native support'
    * Select jni directory -> New folder -> Advanced -> Linked folder : mobile-sdk-harness/src
    * Pass COMPILE_CPP_11=1 to ndk-build to build cpp11
* The platform needs an API key to operate. Sign up at https://www.eegeo.com/developers/ to get your API key and introduce it into the following line in jni/main.cpp : 
  const std::string API_KEY "OBTAIN API_KEY FROM https://www.eegeo.com/developers/ AND INSERT IT HERE"
* Build and debug from within ADT Eclipse
* build.sh can be used to generate the native library if you want to manually package the .apk
* Scroll between the examples using the Next and Previous buttons, or select the example from the drop-down list; the current example name is displayed at the top of the screen. 
* To build at the command line, run ./build -p android from the repository root.
* The project is configured to build for multiple target CPU architectures, creating a universal .apk containing exectutables for each of these architectures.
       * The supported architectures are defined in ./Android/jni/Application.mk, by the line:
               APP_ABI := armeabi,armeabi-v7a,arm64-v8a
       * Removing the APP_ABI line will build and package for the default armeabi architecture. The armeabi architecture is backwards-compatible with armeabi-v7a, but will not run on devices 64-bit Arm instruction sets.
       * For further information about supporting multiple architectures see: http://developer.android.com/google/play/publishing/multiple-apks.html

C++03 Only Builds
=================
It's possible to build C++03 only versions of the application. To do this, you'll need to pull down a C\++03 version of the SDK.
* `./update.platform.sh -p [ios|android] -c` will fetch c\++03/libc++ ABI compatible versions of the SDK for libc++
* `./build -p [ios|android] -c` from the command line will build targeting c\++03 / libc++
* For Android builds, add `COMPILE_CPP_03=1` to your ndkbuild command
* For CMake builds, add `DCOMPILE_CPP_03=1` to your cmake command. e.g. `cmake -G Xcode -DCOMPILE_CPP_03=1 ..`

Staying up to date
==================
Note that the eeGeo SDK is continuously improved. In order to take advantage of the latest features and fixes, developers should run the update.platform.sh script frequently to build against the latest version of the SDK. This is important, because as we improve our map data, old versions of the SDK may lose the ability to load it. By taking frequent SDK updates, the cost of keeping up to date with the latest SDK version will be low, and you will always be able to use the latest and best data.

[![](http://apikey.eegeo.com/tracker/UA-21564666-7/mobile-sdk-harness-readme)]()
