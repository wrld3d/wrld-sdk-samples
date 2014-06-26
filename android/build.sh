#!/usr/bin/env sh

rm -rf build.android
mkdir build.android
pushd .
cd build.android
# todo -- parameterise on NDK location
export ANDROID_NDK=~/Desktop/droid/android-ndk-r8e/
export ANDROID_ABI=armeabi
cmake -Wno-dev -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/android/android.toolchain.cmake -DANDROID_NATIVE_API_LEVEL=9 ..
make -j8
resultcode=$?

if [ $resultcode = 0 ] ; then
	cp -R ../src ./src
	cp -R ../assets ./assets
	cp -R ../res ./res
	cp ../AndroidManifest.xml ./AndroidManifest.xml
	mkdir ./libs/
	cp -R ../libs/armeabi-v7a ./libs/armeabi-v7a
	mv ./libs/armeabi-v7a/libplatform-sdk.so ./libs/armeabi-v7a/libnative-activity.so
	android update project --target android-17 --name my-project --path .
	# todo -- parameterise on ant debug/release
	ant debug 
	resultcode=$?
fi

popd

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi


exit $resultcode
