#!/bin/sh

mkb --buildenv=SCONS --debug
mkb --buildenv=SCONS --debug --deploy=android

adb uninstall com.mycompany.s3eflurry
adb install build_s3eflurry_scons_x86/deployments/default/android/debug/s3eFlurry.apk