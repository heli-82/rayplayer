# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/heli/Projects/cpp/ray_player

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heli/Projects/cpp/ray_player/build

# Include any dependencies generated for this target.
include CMakeFiles/ray.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ray.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ray.dir/flags.make

CMakeFiles/ray.dir/main.cpp.o: CMakeFiles/ray.dir/flags.make
CMakeFiles/ray.dir/main.cpp.o: /home/heli/Projects/cpp/ray_player/main.cpp
CMakeFiles/ray.dir/main.cpp.o: CMakeFiles/ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/heli/Projects/cpp/ray_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ray.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ray.dir/main.cpp.o -MF CMakeFiles/ray.dir/main.cpp.o.d -o CMakeFiles/ray.dir/main.cpp.o -c /home/heli/Projects/cpp/ray_player/main.cpp

CMakeFiles/ray.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ray.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heli/Projects/cpp/ray_player/main.cpp > CMakeFiles/ray.dir/main.cpp.i

CMakeFiles/ray.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ray.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heli/Projects/cpp/ray_player/main.cpp -o CMakeFiles/ray.dir/main.cpp.s

# Object files for target ray
ray_OBJECTS = \
"CMakeFiles/ray.dir/main.cpp.o"

# External object files for target ray
ray_EXTERNAL_OBJECTS =

ray: CMakeFiles/ray.dir/main.cpp.o
ray: CMakeFiles/ray.dir/build.make
ray: /usr/lib/libraylib.so
ray: nativefiledialog-extended/src/libnfd.a
ray: /usr/lib/libtag.so.2.0.2
ray: /usr/lib/libgtk-3.so
ray: /usr/lib/libgdk-3.so
ray: /usr/lib/libz.so
ray: /usr/lib/libharfbuzz.so
ray: /usr/lib/libpangocairo-1.0.so
ray: /usr/lib/libpango-1.0.so
ray: /usr/lib/libatk-1.0.so
ray: /usr/lib/libcairo.so
ray: /usr/lib/libcairo-gobject.so
ray: /usr/lib/libgdk_pixbuf-2.0.so
ray: /usr/lib/libgio-2.0.so
ray: /usr/lib/libglib-2.0.so
ray: /usr/lib/libgobject-2.0.so
ray: CMakeFiles/ray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/heli/Projects/cpp/ray_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ray"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ray.dir/build: ray
.PHONY : CMakeFiles/ray.dir/build

CMakeFiles/ray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ray.dir/clean

CMakeFiles/ray.dir/depend:
	cd /home/heli/Projects/cpp/ray_player/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heli/Projects/cpp/ray_player /home/heli/Projects/cpp/ray_player /home/heli/Projects/cpp/ray_player/build /home/heli/Projects/cpp/ray_player/build /home/heli/Projects/cpp/ray_player/build/CMakeFiles/ray.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ray.dir/depend

