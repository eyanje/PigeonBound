@echo off

pushd build-windows
mingw32-make
popd
move build-windows\PigeonBound.exe game\PigeonBound.exe
pushd game
.\PigeonBound
popd
