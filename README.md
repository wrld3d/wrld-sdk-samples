eeGeo 3D Maps mobile-sdk-harness
================================

Additional documentation available at http://www.eegeo.com/developers/documentation/

iOS
===

* Run ./update.platform.sh -p ios to get the latest platform libraries and headers.
* The accompanying project has no code signing, so run in the simulator (or provide your own credentials).
* The platform needs an API key to operate. Sign up at https://www.eegeo.com/developers/ to get your API key and introduce it into the following line in ViewController.mm : 
	const std::string API_KEY "OBTAIN API_KEY FROM https://www.eegeo.com/developers/ AND INSERT IT HERE".
* Scroll between the examples using the Next and Previous buttons; the current example name is displayed at the top of the screen.
* To build at the command line, run ./build -p ios from the repository root.

Android
=======
Note - In order to run, your version of Android Developer Tools must be >= 22.6
In order to support 64-bit ABIs, you must be using Android NDK revision 10d or later:
http://developer.android.com/tools/sdk/ndk/index.html#Revisions

* Install the Android SDK and NDK
* Run ./update.platform.sh -p android to get the latest platform libraries and headers.
* Open an ADT Eclipse workspace, importing the cloned repository as an Android project
* Configure your workspace:
    * File -> Import -> Android: 'Existing Android Code Into Workspace'
    * Select the 'android' directory in the repository
    * ADT -> Preferences -> Android -> NDK : Set NDK location to the root of your NDK directory
    * Select imported activity -> Android Tools : 'Add native support'
    * Select jni directory -> New folder -> Advanced -> Linked folder : mobile-sdk-harness/src
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

iOS c++11 support
=================
* ./update.platform.sh -p ios -c will fetch c++11/libc++ ABI compatible versions of the SDK for libc++
* ./build -p ios -c from the command line will build targeting c++11 / libc++
* An additional target in the XCode project file is provided for c++11 support: SDKSamplesAppCpp11

android c++11 support
=====================
* Android c++11 support is EXPERIMENTAL due to the experimental nature of c++11 support in the NDK (see https://developer.android.com/tools/sdk/ndk/index.html & https://gcc.gnu.org/gcc-4.8/cxx0x_status.html)
* Only tested against Android NDK version r10d - https://developer.android.com/tools/sdk/ndk/index.html
* Only tested against gcc 4.9 & gnu libstd++ (see android/jni/Application.mk for how to target these)
* ./update.platform.sh -p android -c will fetch c++11/gnu libstdc++ ABI compatible versions of the SDK
* ./build -p android -c from the command line will build targeting c++11
* Pass COMPILE_CPP_11=1 to ndk-build to build cpp11

Staying up to date
==================
Note that the eeGeo SDK is continuously improved. In order to take advantage of the latest features and fixes, developers should run the update.platform.sh script frequently to build against the latest version of the SDK. This is important, because as we improve our map data, old versions of the SDK may lose the ability to load it. By taking frequent SDK updates, the cost of keeping up to date with the latest SDK version will be low, and you will always be able to use the latest and best data.

[![](http://apikey.eegeo.com/tracker/UA-21564666-7/mobile-sdk-harness-readme)]()
