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
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ronaldhg/Escritorio/CProgram

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ronaldhg/Escritorio/CProgram/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CProgram.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CProgram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CProgram.dir/flags.make

CMakeFiles/CProgram.dir/preprocesador.c.o: CMakeFiles/CProgram.dir/flags.make
CMakeFiles/CProgram.dir/preprocesador.c.o: ../preprocesador.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ronaldhg/Escritorio/CProgram/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CProgram.dir/preprocesador.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CProgram.dir/preprocesador.c.o   -c /home/ronaldhg/Escritorio/CProgram/preprocesador.c

CMakeFiles/CProgram.dir/preprocesador.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CProgram.dir/preprocesador.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ronaldhg/Escritorio/CProgram/preprocesador.c > CMakeFiles/CProgram.dir/preprocesador.c.i

CMakeFiles/CProgram.dir/preprocesador.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CProgram.dir/preprocesador.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ronaldhg/Escritorio/CProgram/preprocesador.c -o CMakeFiles/CProgram.dir/preprocesador.c.s

# Object files for target CProgram
CProgram_OBJECTS = \
"CMakeFiles/CProgram.dir/preprocesador.c.o"

# External object files for target CProgram
CProgram_EXTERNAL_OBJECTS =

CProgram: CMakeFiles/CProgram.dir/preprocesador.c.o
CProgram: CMakeFiles/CProgram.dir/build.make
CProgram: CMakeFiles/CProgram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ronaldhg/Escritorio/CProgram/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CProgram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CProgram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CProgram.dir/build: CProgram

.PHONY : CMakeFiles/CProgram.dir/build

CMakeFiles/CProgram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CProgram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CProgram.dir/clean

CMakeFiles/CProgram.dir/depend:
	cd /home/ronaldhg/Escritorio/CProgram/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ronaldhg/Escritorio/CProgram /home/ronaldhg/Escritorio/CProgram /home/ronaldhg/Escritorio/CProgram/cmake-build-debug /home/ronaldhg/Escritorio/CProgram/cmake-build-debug /home/ronaldhg/Escritorio/CProgram/cmake-build-debug/CMakeFiles/CProgram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CProgram.dir/depend

