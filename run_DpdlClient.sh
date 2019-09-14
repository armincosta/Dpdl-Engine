#!/bin/sh
echo "starting DpdlClient..."
java -cp ./DpdlEngine_V1.0_release.jar:./lib/:./lib/bluecove-2.1.0.jar dpdl.dpdlRun.DpdlClient
echo $?
