# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = F:\Code\JetBrains\ToolBox\apps\CLion\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = F:\Code\JetBrains\ToolBox\apps\CLion\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project\GitHub\DongmenDB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project\GitHub\DongmenDB\cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/utils.dir/flags.make

src/CMakeFiles/utils.dir/utils/utils.cpp.obj: src/CMakeFiles/utils.dir/flags.make
src/CMakeFiles/utils.dir/utils/utils.cpp.obj: src/CMakeFiles/utils.dir/includes_CXX.rsp
src/CMakeFiles/utils.dir/utils/utils.cpp.obj: ../src/utils/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\GitHub\DongmenDB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/utils.dir/utils/utils.cpp.obj"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && F:\Code\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\utils.dir\utils\utils.cpp.obj -c D:\Project\GitHub\DongmenDB\src\utils\utils.cpp

src/CMakeFiles/utils.dir/utils/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/utils/utils.cpp.i"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && F:\Code\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\GitHub\DongmenDB\src\utils\utils.cpp > CMakeFiles\utils.dir\utils\utils.cpp.i

src/CMakeFiles/utils.dir/utils/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/utils/utils.cpp.s"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && F:\Code\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\GitHub\DongmenDB\src\utils\utils.cpp -o CMakeFiles\utils.dir\utils\utils.cpp.s

src/CMakeFiles/utils.dir/utils/utils.cpp.obj.requires:

.PHONY : src/CMakeFiles/utils.dir/utils/utils.cpp.obj.requires

src/CMakeFiles/utils.dir/utils/utils.cpp.obj.provides: src/CMakeFiles/utils.dir/utils/utils.cpp.obj.requires
	$(MAKE) -f src\CMakeFiles\utils.dir\build.make src/CMakeFiles/utils.dir/utils/utils.cpp.obj.provides.build
.PHONY : src/CMakeFiles/utils.dir/utils/utils.cpp.obj.provides

src/CMakeFiles/utils.dir/utils/utils.cpp.obj.provides.build: src/CMakeFiles/utils.dir/utils/utils.cpp.obj


# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/utils/utils.cpp.obj"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

../lib/libutilsd.a: src/CMakeFiles/utils.dir/utils/utils.cpp.obj
../lib/libutilsd.a: src/CMakeFiles/utils.dir/build.make
../lib/libutilsd.a: src/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project\GitHub\DongmenDB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\lib\libutilsd.a"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && $(CMAKE_COMMAND) -P CMakeFiles\utils.dir\cmake_clean_target.cmake
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\utils.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/utils.dir/build: ../lib/libutilsd.a

.PHONY : src/CMakeFiles/utils.dir/build

src/CMakeFiles/utils.dir/requires: src/CMakeFiles/utils.dir/utils/utils.cpp.obj.requires

.PHONY : src/CMakeFiles/utils.dir/requires

src/CMakeFiles/utils.dir/clean:
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\src && $(CMAKE_COMMAND) -P CMakeFiles\utils.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/utils.dir/clean

src/CMakeFiles/utils.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\GitHub\DongmenDB D:\Project\GitHub\DongmenDB\src D:\Project\GitHub\DongmenDB\cmake-build-debug D:\Project\GitHub\DongmenDB\cmake-build-debug\src D:\Project\GitHub\DongmenDB\cmake-build-debug\src\CMakeFiles\utils.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/utils.dir/depend

