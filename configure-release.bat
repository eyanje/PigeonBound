@echo off

pushd build-windows
cmake -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=RELEASE ..
popd
