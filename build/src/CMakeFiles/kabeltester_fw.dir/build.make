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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.20.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.20.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/andersn/Fritid/Kabeltester

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/andersn/Fritid/Kabeltester/build

# Include any dependencies generated for this target.
include src/CMakeFiles/kabeltester_fw.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/kabeltester_fw.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/kabeltester_fw.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/kabeltester_fw.dir/flags.make

src/CMakeFiles/kabeltester_fw.dir/main.c.obj: src/CMakeFiles/kabeltester_fw.dir/flags.make
src/CMakeFiles/kabeltester_fw.dir/main.c.obj: ../src/main.c
src/CMakeFiles/kabeltester_fw.dir/main.c.obj: src/CMakeFiles/kabeltester_fw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andersn/Fritid/Kabeltester/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/kabeltester_fw.dir/main.c.obj"
	cd /Users/andersn/Fritid/Kabeltester/build/src && /usr/local/homebrew/opt/avr-gcc@11/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/kabeltester_fw.dir/main.c.obj -MF CMakeFiles/kabeltester_fw.dir/main.c.obj.d -o CMakeFiles/kabeltester_fw.dir/main.c.obj -c /Users/andersn/Fritid/Kabeltester/src/main.c

src/CMakeFiles/kabeltester_fw.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kabeltester_fw.dir/main.c.i"
	cd /Users/andersn/Fritid/Kabeltester/build/src && /usr/local/homebrew/opt/avr-gcc@11/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/andersn/Fritid/Kabeltester/src/main.c > CMakeFiles/kabeltester_fw.dir/main.c.i

src/CMakeFiles/kabeltester_fw.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kabeltester_fw.dir/main.c.s"
	cd /Users/andersn/Fritid/Kabeltester/build/src && /usr/local/homebrew/opt/avr-gcc@11/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/andersn/Fritid/Kabeltester/src/main.c -o CMakeFiles/kabeltester_fw.dir/main.c.s

# Object files for target kabeltester_fw
kabeltester_fw_OBJECTS = \
"CMakeFiles/kabeltester_fw.dir/main.c.obj"

# External object files for target kabeltester_fw
kabeltester_fw_EXTERNAL_OBJECTS =

src/kabeltester_fw.elf: src/CMakeFiles/kabeltester_fw.dir/main.c.obj
src/kabeltester_fw.elf: src/CMakeFiles/kabeltester_fw.dir/build.make
src/kabeltester_fw.elf: gpio/libgpio.a
src/kabeltester_fw.elf: src/CMakeFiles/kabeltester_fw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andersn/Fritid/Kabeltester/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable kabeltester_fw.elf"
	cd /Users/andersn/Fritid/Kabeltester/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kabeltester_fw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/kabeltester_fw.dir/build: src/kabeltester_fw.elf
.PHONY : src/CMakeFiles/kabeltester_fw.dir/build

src/CMakeFiles/kabeltester_fw.dir/clean:
	cd /Users/andersn/Fritid/Kabeltester/build/src && $(CMAKE_COMMAND) -P CMakeFiles/kabeltester_fw.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/kabeltester_fw.dir/clean

src/CMakeFiles/kabeltester_fw.dir/depend:
	cd /Users/andersn/Fritid/Kabeltester/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andersn/Fritid/Kabeltester /Users/andersn/Fritid/Kabeltester/src /Users/andersn/Fritid/Kabeltester/build /Users/andersn/Fritid/Kabeltester/build/src /Users/andersn/Fritid/Kabeltester/build/src/CMakeFiles/kabeltester_fw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/kabeltester_fw.dir/depend

