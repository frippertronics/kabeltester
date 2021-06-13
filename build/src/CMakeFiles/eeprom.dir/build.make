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

# Utility rule file for eeprom.

# Include any custom commands dependencies for this target.
include src/CMakeFiles/eeprom.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/eeprom.dir/progress.make

src/CMakeFiles/eeprom:
	cd /Users/andersn/Fritid/Kabeltester/build/src && avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex kabeltester_fw.elf kabeltester_fw.eep

eeprom: src/CMakeFiles/eeprom
eeprom: src/CMakeFiles/eeprom.dir/build.make
.PHONY : eeprom

# Rule to build all files generated by this target.
src/CMakeFiles/eeprom.dir/build: eeprom
.PHONY : src/CMakeFiles/eeprom.dir/build

src/CMakeFiles/eeprom.dir/clean:
	cd /Users/andersn/Fritid/Kabeltester/build/src && $(CMAKE_COMMAND) -P CMakeFiles/eeprom.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/eeprom.dir/clean

src/CMakeFiles/eeprom.dir/depend:
	cd /Users/andersn/Fritid/Kabeltester/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andersn/Fritid/Kabeltester /Users/andersn/Fritid/Kabeltester/src /Users/andersn/Fritid/Kabeltester/build /Users/andersn/Fritid/Kabeltester/build/src /Users/andersn/Fritid/Kabeltester/build/src/CMakeFiles/eeprom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/eeprom.dir/depend

