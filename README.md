# PigeonBound

A simple game for my AP Computer Science class

Do not use this as an example for anything

## Downloading

Run
```
git clone https://github.com/eyanje/PigeonBound.git
```
And git will clone all the files into PigeonBound/

### Dependencies

There is a list of dependencies to install.
Because I suck with git and CMake, I will give them to you as a list.

These folders should all be 

- freetype-2.9.1
- glew-2.1.0
- SDL2_mixer-2.0.4
    - SDL2_mixer-2.0.4-windows
- SDL2-2.0.9
- stb

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
to build the game. gdb will still debug the game.

The final executable file can be found in game,
which can now be moved elsewhere.