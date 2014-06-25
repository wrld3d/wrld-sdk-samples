#!/usr/bin/env sh

# todo -- parameterise on NDK location
sh do_make.sh ~/Desktop/droid/android-ndk-r8e/ debug

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi


exit $resultcode
