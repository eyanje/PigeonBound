# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\eyanj\programming\cmake-3.13.2-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\eyanj\programming\cmake-3.13.2-win64-x64\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\eyanj\programming\PigeonBound

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\eyanj\programming\PigeonBound\build-windows

# Include any dependencies generated for this target.
include CMakeFiles/PigeonBound.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PigeonBound.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PigeonBound.dir/flags.make

CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj: CMakeFiles/PigeonBound.dir/flags.make
CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj: CMakeFiles/PigeonBound.dir/includes_CXX.rsp
CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj: ../src/pigeonbound.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\eyanj\programming\PigeonBound\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\PigeonBound.dir\src\pigeonbound.cpp.obj -c C:\Users\eyanj\programming\PigeonBound\src\pigeonbound.cpp

CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\eyanj\programming\PigeonBound\src\pigeonbound.cpp > CMakeFiles\PigeonBound.dir\src\pigeonbound.cpp.i

CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\eyanj\programming\PigeonBound\src\pigeonbound.cpp -o CMakeFiles\PigeonBound.dir\src\pigeonbound.cpp.s

# Object files for target PigeonBound
PigeonBound_OBJECTS = \
"CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj"

# External object files for target PigeonBound
PigeonBound_EXTERNAL_OBJECTS =

PigeonBound.exe: CMakeFiles/PigeonBound.dir/src/pigeonbound.cpp.obj
PigeonBound.exe: CMakeFiles/PigeonBound.dir/build.make
PigeonBound.exe: CMakeFiles/PigeonBound.dir/linklibs.rsp
PigeonBound.exe: CMakeFiles/PigeonBound.dir/objects1.rsp
PigeonBound.exe: CMakeFiles/PigeonBound.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\eyanj\programming\PigeonBound\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PigeonBound.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PigeonBound.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PigeonBound.dir/build: PigeonBound.exe

.PHONY : CMakeFiles/PigeonBound.dir/build

CMakeFiles/PigeonBound.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PigeonBound.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PigeonBound.dir/clean

CMakeFiles/PigeonBound.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\eyanj\programming\PigeonBound C:\Users\eyanj\programming\PigeonBound C:\Users\eyanj\programming\PigeonBound\build-windows C:\Users\eyanj\programming\PigeonBound\build-windows C:\Users\eyanj\programming\PigeonBound\build-windows\CMakeFiles\PigeonBound.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PigeonBound.dir/depend

