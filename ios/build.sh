#!/bin/sh

usage() { echo "Usage: $0 -p ios"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

projectPath=$(pwd)/./XcodeBuild
rm -rf $projectPath

targetName="INVALID"

while getopts "p:c" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               usage
            fi
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

targetName="SDKSamplesApp"

mkdir -p $projectPath

(cd $projectPath && cmake -G Xcode ..)

if [ $? -ne 0 ]; then
  echo "FAILED TO GENERATE PROJECT"
  exit $?
fi 

(cd $projectPath && xcodebuild -target $targetName -arch "i386" -sdk "iphonesimulator")
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
