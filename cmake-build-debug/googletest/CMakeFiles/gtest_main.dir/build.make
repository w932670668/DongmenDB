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
include googletest/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include googletest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include googletest/CMakeFiles/gtest_main.dir/flags.make

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: googletest/CMakeFiles/gtest_main.dir/flags.make
googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: googletest/CMakeFiles/gtest_main.dir/includes_CXX.rsp
googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj: ../googletest/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\GitHub\DongmenDB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && F:\Code\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj -c D:\Project\GitHub\DongmenDB\googletest\src\gtest_main.cc

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && F:\Code\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\GitHub\DongmenDB\googletest\src\gtest_main.cc > CMakeFiles\gtest_main.dir\src\gtest_main.cc.i

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && F:\Code\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\GitHub\DongmenDB\googletest\src\gtest_main.cc -o CMakeFiles\gtest_main.dir\src\gtest_main.cc.s

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.requires:

.PHONY : googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.requires

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.provides: googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.requires
	$(MAKE) -f googletest\CMakeFiles\gtest_main.dir\build.make googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.provides.build
.PHONY : googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.provides

googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.provides.build: googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj


# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

../lib/libgtest_maind.a: googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj
../lib/libgtest_maind.a: googletest/CMakeFiles/gtest_main.dir/build.make
../lib/libgtest_maind.a: googletest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project\GitHub\DongmenDB\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\lib\libgtest_maind.a"
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && $(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean_target.cmake
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gtest_main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest/CMakeFiles/gtest_main.dir/build: ../lib/libgtest_maind.a

.PHONY : googletest/CMakeFiles/gtest_main.dir/build

googletest/CMakeFiles/gtest_main.dir/requires: googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj.requires

.PHONY : googletest/CMakeFiles/gtest_main.dir/requires

googletest/CMakeFiles/gtest_main.dir/clean:
	cd /d D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest && $(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean.cmake
.PHONY : googletest/CMakeFiles/gtest_main.dir/clean

googletest/CMakeFiles/gtest_main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\GitHub\DongmenDB D:\Project\GitHub\DongmenDB\googletest D:\Project\GitHub\DongmenDB\cmake-build-debug D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest D:\Project\GitHub\DongmenDB\cmake-build-debug\googletest\CMakeFiles\gtest_main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : googletest/CMakeFiles/gtest_main.dir/depend

