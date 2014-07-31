#!/usr/bin/env sh

usage() { echo "Usage: $0 [-c]"; echo "  -c -> cpp11 support"; 1>&2; exit 1; }

compile_cpp_11="0"

while getopts "c" o; do
    case "${o}" in
        c)
            c="cpp11"
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ "$c" == "cpp11" ]; then
   compile_cpp_11="1"
fi

echo $compile_cpp_11

rm -rf build
mkdir build
pushd .
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain/ios/iOS.cmake -DCOMPILE_CPP_11=$compile_cpp_11 -GXcode ..
popd