@echo off

pushd build-windows
cmake -G"MinGW Makefiles" ..
popd
