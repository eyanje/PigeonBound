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
CMAKE_SOURCE_DIR = C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake

# Include any dependencies generated for this target.
include CMakeFiles/glewinfo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glewinfo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glewinfo.dir/flags.make

CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj: CMakeFiles/glewinfo.dir/flags.make
CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj: CMakeFiles/glewinfo.dir/includes_C.rsp
CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj: C:/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\glewinfo.dir\C_\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c.obj   -c C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c

CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c > CMakeFiles\glewinfo.dir\C_\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c.i

CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c -o CMakeFiles\glewinfo.dir\C_\Users\eyanj\programming\PigeonBound\glew-2.1.0\src\glewinfo.c.s

CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc.obj: CMakeFiles/glewinfo.dir/flags.make
CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc.obj: C:/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc.obj"
	C:\MinGW\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\glewinfo.rc CMakeFiles\glewinfo.dir\C_\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\glewinfo.rc.obj

# Object files for target glewinfo
glewinfo_OBJECTS = \
"CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj" \
"CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc.obj"

# External object files for target glewinfo
glewinfo_EXTERNAL_OBJECTS =

bin/glewinfo.exe: CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/src/glewinfo.c.obj
bin/glewinfo.exe: CMakeFiles/glewinfo.dir/C_/Users/eyanj/programming/PigeonBound/glew-2.1.0/build/glewinfo.rc.obj
bin/glewinfo.exe: CMakeFiles/glewinfo.dir/build.make
bin/glewinfo.exe: lib/libglew32.dll.a
bin/glewinfo.exe: CMakeFiles/glewinfo.dir/linklibs.rsp
bin/glewinfo.exe: CMakeFiles/glewinfo.dir/objects1.rsp
bin/glewinfo.exe: CMakeFiles/glewinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin\glewinfo.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glewinfo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glewinfo.dir/build: bin/glewinfo.exe

.PHONY : CMakeFiles/glewinfo.dir/build

CMakeFiles/glewinfo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glewinfo.dir\cmake_clean.cmake
.PHONY : CMakeFiles/glewinfo.dir/clean

CMakeFiles/glewinfo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake C:\Users\eyanj\programming\PigeonBound\glew-2.1.0\build\cmake\CMakeFiles\glewinfo.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glewinfo.dir/depend

