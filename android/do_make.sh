#!/usr/bin/env sh

# call like ---> sh do_make.sh ~/Desktop/droid/android-ndk-r8e/ debug

rm -rf build.android
mkdir build.android
pushd .
echo $(pwd)
cd build.android
export ANDROID_NDK=$1
export ANDROID_ABI=armeabi
cmake -Wno-dev -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/android.toolchain.cmake -DANDROID_NATIVE_API_LEVEL=9 ..
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
	ant $2 
	resultcode=$?
fi

popd
exit $resultcode