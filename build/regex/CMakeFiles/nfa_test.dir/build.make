# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shengguolu/code/regex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shengguolu/code/regex/build

# Include any dependencies generated for this target.
include regex/CMakeFiles/nfa_test.dir/depend.make

# Include the progress variables for this target.
include regex/CMakeFiles/nfa_test.dir/progress.make

# Include the compile flags for this target's objects.
include regex/CMakeFiles/nfa_test.dir/flags.make

regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.o: regex/CMakeFiles/nfa_test.dir/flags.make
regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.o: ../regex/nfa2_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shengguolu/code/regex/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.o"
	cd /Users/shengguolu/code/regex/build/regex && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nfa_test.dir/nfa2_test.cpp.o -c /Users/shengguolu/code/regex/regex/nfa2_test.cpp

regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nfa_test.dir/nfa2_test.cpp.i"
	cd /Users/shengguolu/code/regex/build/regex && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shengguolu/code/regex/regex/nfa2_test.cpp > CMakeFiles/nfa_test.dir/nfa2_test.cpp.i

regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nfa_test.dir/nfa2_test.cpp.s"
	cd /Users/shengguolu/code/regex/build/regex && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shengguolu/code/regex/regex/nfa2_test.cpp -o CMakeFiles/nfa_test.dir/nfa2_test.cpp.s

# Object files for target nfa_test
nfa_test_OBJECTS = \
"CMakeFiles/nfa_test.dir/nfa2_test.cpp.o"

# External object files for target nfa_test
nfa_test_EXTERNAL_OBJECTS =

nfa_test: regex/CMakeFiles/nfa_test.dir/nfa2_test.cpp.o
nfa_test: regex/CMakeFiles/nfa_test.dir/build.make
nfa_test: libnfa.dylib
nfa_test: regex/CMakeFiles/nfa_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/shengguolu/code/regex/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../nfa_test"
	cd /Users/shengguolu/code/regex/build/regex && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nfa_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
regex/CMakeFiles/nfa_test.dir/build: nfa_test

.PHONY : regex/CMakeFiles/nfa_test.dir/build

regex/CMakeFiles/nfa_test.dir/clean:
	cd /Users/shengguolu/code/regex/build/regex && $(CMAKE_COMMAND) -P CMakeFiles/nfa_test.dir/cmake_clean.cmake
.PHONY : regex/CMakeFiles/nfa_test.dir/clean

regex/CMakeFiles/nfa_test.dir/depend:
	cd /Users/shengguolu/code/regex/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shengguolu/code/regex /Users/shengguolu/code/regex/regex /Users/shengguolu/code/regex/build /Users/shengguolu/code/regex/build/regex /Users/shengguolu/code/regex/build/regex/CMakeFiles/nfa_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : regex/CMakeFiles/nfa_test.dir/depend
