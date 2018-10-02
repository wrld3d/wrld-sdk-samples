#!/bin/bash

usage() { echo "Usage: $0 -p android|ios"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

baseUrl="http://s3.amazonaws.com/eegeo-static/"
srcPackageName="INVALID"
destPackageName="./sdk.package.tar.gz"
includeDestination="INVALID"
sdkDestination="INVALID"

while getopts "p:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               if [ "$p" != "android" ]; then
                 usage
               fi
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

if [ "$p" == "ios" ]; then
   srcPackageName="sdk.package.ios.cpp11.tar.gz"
   includeDestination="./ios/Include/eegeo"
   sdkDestination="sdk.package"
elif [ "$p" == "android" ]; then
   srcPackageName="sdk.package.android.cpp11.c++_static.tar.gz"
   includeDestination="./android/libs/eegeo"
   sdkDestination="sdk.package.android"
fi



echo "Updating $p platform..."
rm -f ./$destPackageName
rm -rf $includeDestination

src_url=$(echo $baseUrl$srcPackageName | sed "s:+:%2B:g")
echo "fetching $src_url"

curl $src_url > ./$destPackageName

statuscode=$?
if [ $statuscode -ne 0 ] ; then
    echo "Failed to download sdk package ${baseUrl}${srcPackageName}" >&2
    exit $statuscode
fi   

if [ ! -d `dirname "$includeDestination"` ]; then
    mkdir -p `dirname "$includeDestination"`
fi

tar -zxvf $destPackageName

if [ $? -ne 0 ] ; then
    echo "Failed to unzip sdk package ${destPackageName}"
    exit 1    
fi

rm -f ./$destPackageName
platformVersion=`cat ./$sdkDestination/version.txt`
echo "Platform version --> $platformVersion"
mv ./$sdkDestination $includeDestination
