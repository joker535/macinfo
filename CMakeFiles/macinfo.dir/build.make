# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.20.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.20.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nieyu/tempfile/macinfo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nieyu/tempfile/macinfo

# Include any dependencies generated for this target.
include CMakeFiles/macinfo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/macinfo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/macinfo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/macinfo.dir/flags.make

CMakeFiles/macinfo.dir/c_serial.c.o: CMakeFiles/macinfo.dir/flags.make
CMakeFiles/macinfo.dir/c_serial.c.o: c_serial.c
CMakeFiles/macinfo.dir/c_serial.c.o: CMakeFiles/macinfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nieyu/tempfile/macinfo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/macinfo.dir/c_serial.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/macinfo.dir/c_serial.c.o -MF CMakeFiles/macinfo.dir/c_serial.c.o.d -o CMakeFiles/macinfo.dir/c_serial.c.o -c /Users/nieyu/tempfile/macinfo/c_serial.c

CMakeFiles/macinfo.dir/c_serial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/macinfo.dir/c_serial.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/nieyu/tempfile/macinfo/c_serial.c > CMakeFiles/macinfo.dir/c_serial.c.i

CMakeFiles/macinfo.dir/c_serial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/macinfo.dir/c_serial.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/nieyu/tempfile/macinfo/c_serial.c -o CMakeFiles/macinfo.dir/c_serial.c.s

CMakeFiles/macinfo.dir/example_full.c.o: CMakeFiles/macinfo.dir/flags.make
CMakeFiles/macinfo.dir/example_full.c.o: example_full.c
CMakeFiles/macinfo.dir/example_full.c.o: CMakeFiles/macinfo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nieyu/tempfile/macinfo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/macinfo.dir/example_full.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/macinfo.dir/example_full.c.o -MF CMakeFiles/macinfo.dir/example_full.c.o.d -o CMakeFiles/macinfo.dir/example_full.c.o -c /Users/nieyu/tempfile/macinfo/example_full.c

CMakeFiles/macinfo.dir/example_full.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/macinfo.dir/example_full.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/nieyu/tempfile/macinfo/example_full.c > CMakeFiles/macinfo.dir/example_full.c.i

CMakeFiles/macinfo.dir/example_full.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/macinfo.dir/example_full.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/nieyu/tempfile/macinfo/example_full.c -o CMakeFiles/macinfo.dir/example_full.c.s

# Object files for target macinfo
macinfo_OBJECTS = \
"CMakeFiles/macinfo.dir/c_serial.c.o" \
"CMakeFiles/macinfo.dir/example_full.c.o"

# External object files for target macinfo
macinfo_EXTERNAL_OBJECTS =

macinfo: CMakeFiles/macinfo.dir/c_serial.c.o
macinfo: CMakeFiles/macinfo.dir/example_full.c.o
macinfo: CMakeFiles/macinfo.dir/build.make
macinfo: CMakeFiles/macinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nieyu/tempfile/macinfo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable macinfo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/macinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/macinfo.dir/build: macinfo
.PHONY : CMakeFiles/macinfo.dir/build

CMakeFiles/macinfo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/macinfo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/macinfo.dir/clean

CMakeFiles/macinfo.dir/depend:
	cd /Users/nieyu/tempfile/macinfo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nieyu/tempfile/macinfo /Users/nieyu/tempfile/macinfo /Users/nieyu/tempfile/macinfo /Users/nieyu/tempfile/macinfo /Users/nieyu/tempfile/macinfo/CMakeFiles/macinfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/macinfo.dir/depend

