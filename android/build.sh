#!/usr/bin/env sh

usage() { echo "Usage: $0 -p android [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp11 support"; 1>&2; exit 1; }

projectPath=$(pwd)/./
compile_cpp_11="0"

while getopts "p:c" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "android" ]; then
               usage
            fi
            ;;
        c)
            c="cpp11"
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${p}" ]; then
    usage
fi

if [ "$c" == "cpp11" ]; then
   compile_cpp_11="1"
fi

rm -rf build.android
mkdir build.android
pushd .
cd build.android
# todo -- parameterise on NDK location
export ANDROID_NDK=~/Desktop/droid/android-ndk-r9d/
export ANDROID_ABI=armeabi

cmake -Wno-dev \
      -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/android/android.toolchain.cmake \
      -DANDROID_NATIVE_API_LEVEL=9 \
      -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.8 \
      -DCOMPILE_CPP_11=$compile_cpp_11 \
      ..

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
