#!/usr/bin/env sh

rm -rf build.android
mkdir build.android
pushd .
echo $(pwd)
cd build.android
export ANDROID_NDK=$1
export ANDROID_HOME=$2
/usr/bin/cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/android.toolchain.cmake -DANDROID_NATIVE_API_LEVEL=9 ..
make -j8
cp ../AndroidManifest.xml ./AndroidManifest.xml
cp -R ../src ./src
cp -R ../assets ./assets
cp -R ../res ./res
android update project --target android-17 --name my-project --path .
ant debug 
#ant install
popd