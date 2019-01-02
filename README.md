# PigeonBound

A simple game for my AP Computer Science class

Do not use this as an example for anything

## Downloading

Run
```
git clone https://github.com/eyanje/PigeonBound.git
```
And git will clone all the files into PigeonBound/

## Compiling

### Windows

To compile PigeonBound for Windows, you will need CMake 3.1.2
and MinGW with g++ and mingw32-make.

#### Debug version

PigeonBound can be compiled with CMake and MinGW.

Run 
```
.\configure
```
and CMake will create a makefile for mingw32

Then, whenever a file is modified, run
```
.\build
```
MinGW will compile and debug the game.

The executable file can be found in game/

#### Release version

If you want a version of the game without the command line, you should create the release version instead.

Run 
```
.\configure-release
```
and CMake will create a makefile for the release version

Run
```
.\build
```
to build the game. Gdb will still debug the game.

The final executable file can be found in game,
which can now be moved elsewhere.