# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.oWoqYrIao7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.oWoqYrIao7/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/semestralka.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/semestralka.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/semestralka.dir/flags.make

CMakeFiles/semestralka.dir/main.cpp.o: CMakeFiles/semestralka.dir/flags.make
CMakeFiles/semestralka.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.oWoqYrIao7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/semestralka.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/semestralka.dir/main.cpp.o -c /tmp/tmp.oWoqYrIao7/main.cpp

CMakeFiles/semestralka.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/semestralka.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.oWoqYrIao7/main.cpp > CMakeFiles/semestralka.dir/main.cpp.i

CMakeFiles/semestralka.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/semestralka.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.oWoqYrIao7/main.cpp -o CMakeFiles/semestralka.dir/main.cpp.s

CMakeFiles/semestralka.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/semestralka.dir/main.cpp.o.requires

CMakeFiles/semestralka.dir/main.cpp.o.provides: CMakeFiles/semestralka.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/semestralka.dir/build.make CMakeFiles/semestralka.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/semestralka.dir/main.cpp.o.provides

CMakeFiles/semestralka.dir/main.cpp.o.provides.build: CMakeFiles/semestralka.dir/main.cpp.o


# Object files for target semestralka
semestralka_OBJECTS = \
"CMakeFiles/semestralka.dir/main.cpp.o"

# External object files for target semestralka
semestralka_EXTERNAL_OBJECTS =

semestralka: CMakeFiles/semestralka.dir/main.cpp.o
semestralka: CMakeFiles/semestralka.dir/build.make
semestralka: CMakeFiles/semestralka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.oWoqYrIao7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable semestralka"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/semestralka.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/semestralka.dir/build: semestralka

.PHONY : CMakeFiles/semestralka.dir/build

CMakeFiles/semestralka.dir/requires: CMakeFiles/semestralka.dir/main.cpp.o.requires

.PHONY : CMakeFiles/semestralka.dir/requires

CMakeFiles/semestralka.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/semestralka.dir/cmake_clean.cmake
.PHONY : CMakeFiles/semestralka.dir/clean

CMakeFiles/semestralka.dir/depend:
	cd /tmp/tmp.oWoqYrIao7/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.oWoqYrIao7 /tmp/tmp.oWoqYrIao7 /tmp/tmp.oWoqYrIao7/cmake-build-debug /tmp/tmp.oWoqYrIao7/cmake-build-debug /tmp/tmp.oWoqYrIao7/cmake-build-debug/CMakeFiles/semestralka.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/semestralka.dir/depend

