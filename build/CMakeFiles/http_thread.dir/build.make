# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /root/my_webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/my_webserver/build

# Include any dependencies generated for this target.
include CMakeFiles/http_thread.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/http_thread.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/http_thread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/http_thread.dir/flags.make

CMakeFiles/http_thread.dir/main.cpp.o: CMakeFiles/http_thread.dir/flags.make
CMakeFiles/http_thread.dir/main.cpp.o: ../main.cpp
CMakeFiles/http_thread.dir/main.cpp.o: CMakeFiles/http_thread.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/my_webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/http_thread.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/http_thread.dir/main.cpp.o -MF CMakeFiles/http_thread.dir/main.cpp.o.d -o CMakeFiles/http_thread.dir/main.cpp.o -c /root/my_webserver/main.cpp

CMakeFiles/http_thread.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http_thread.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/my_webserver/main.cpp > CMakeFiles/http_thread.dir/main.cpp.i

CMakeFiles/http_thread.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http_thread.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/my_webserver/main.cpp -o CMakeFiles/http_thread.dir/main.cpp.s

CMakeFiles/http_thread.dir/http_conn.cpp.o: CMakeFiles/http_thread.dir/flags.make
CMakeFiles/http_thread.dir/http_conn.cpp.o: ../http_conn.cpp
CMakeFiles/http_thread.dir/http_conn.cpp.o: CMakeFiles/http_thread.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/my_webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/http_thread.dir/http_conn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/http_thread.dir/http_conn.cpp.o -MF CMakeFiles/http_thread.dir/http_conn.cpp.o.d -o CMakeFiles/http_thread.dir/http_conn.cpp.o -c /root/my_webserver/http_conn.cpp

CMakeFiles/http_thread.dir/http_conn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http_thread.dir/http_conn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/my_webserver/http_conn.cpp > CMakeFiles/http_thread.dir/http_conn.cpp.i

CMakeFiles/http_thread.dir/http_conn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http_thread.dir/http_conn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/my_webserver/http_conn.cpp -o CMakeFiles/http_thread.dir/http_conn.cpp.s

# Object files for target http_thread
http_thread_OBJECTS = \
"CMakeFiles/http_thread.dir/main.cpp.o" \
"CMakeFiles/http_thread.dir/http_conn.cpp.o"

# External object files for target http_thread
http_thread_EXTERNAL_OBJECTS =

http_thread: CMakeFiles/http_thread.dir/main.cpp.o
http_thread: CMakeFiles/http_thread.dir/http_conn.cpp.o
http_thread: CMakeFiles/http_thread.dir/build.make
http_thread: CMakeFiles/http_thread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/my_webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable http_thread"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http_thread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/http_thread.dir/build: http_thread
.PHONY : CMakeFiles/http_thread.dir/build

CMakeFiles/http_thread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/http_thread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/http_thread.dir/clean

CMakeFiles/http_thread.dir/depend:
	cd /root/my_webserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/my_webserver /root/my_webserver /root/my_webserver/build /root/my_webserver/build /root/my_webserver/build/CMakeFiles/http_thread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/http_thread.dir/depend

