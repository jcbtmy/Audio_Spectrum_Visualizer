# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/jacobtoomey/Projects/cpp/Graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jacobtoomey/Projects/cpp/Graphics/build

# Include any dependencies generated for this target.
include CMakeFiles/Graphics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Graphics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Graphics.dir/flags.make

CMakeFiles/Graphics.dir/src/main.cpp.o: CMakeFiles/Graphics.dir/flags.make
CMakeFiles/Graphics.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jacobtoomey/Projects/cpp/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Graphics.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Graphics.dir/src/main.cpp.o -c /home/jacobtoomey/Projects/cpp/Graphics/src/main.cpp

CMakeFiles/Graphics.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jacobtoomey/Projects/cpp/Graphics/src/main.cpp > CMakeFiles/Graphics.dir/src/main.cpp.i

CMakeFiles/Graphics.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jacobtoomey/Projects/cpp/Graphics/src/main.cpp -o CMakeFiles/Graphics.dir/src/main.cpp.s

# Object files for target Graphics
Graphics_OBJECTS = \
"CMakeFiles/Graphics.dir/src/main.cpp.o"

# External object files for target Graphics
Graphics_EXTERNAL_OBJECTS =

Graphics: CMakeFiles/Graphics.dir/src/main.cpp.o
Graphics: CMakeFiles/Graphics.dir/build.make
Graphics: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Graphics: /usr/lib/x86_64-linux-gnu/libGLX.so
Graphics: /usr/lib/x86_64-linux-gnu/libGLU.so
Graphics: /usr/lib/x86_64-linux-gnu/libglut.so
Graphics: CMakeFiles/Graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jacobtoomey/Projects/cpp/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Graphics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graphics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Graphics.dir/build: Graphics

.PHONY : CMakeFiles/Graphics.dir/build

CMakeFiles/Graphics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Graphics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Graphics.dir/clean

CMakeFiles/Graphics.dir/depend:
	cd /home/jacobtoomey/Projects/cpp/Graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jacobtoomey/Projects/cpp/Graphics /home/jacobtoomey/Projects/cpp/Graphics /home/jacobtoomey/Projects/cpp/Graphics/build /home/jacobtoomey/Projects/cpp/Graphics/build /home/jacobtoomey/Projects/cpp/Graphics/build/CMakeFiles/Graphics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Graphics.dir/depend

