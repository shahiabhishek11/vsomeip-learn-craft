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
CMAKE_SOURCE_DIR = /home/sdv-2534/Documents/NVD/NVDReqRes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sdv-2534/Documents/NVD/NVDReqRes/build

# Include any dependencies generated for this target.
include CMakeFiles/nvd_response.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nvd_response.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nvd_response.dir/flags.make

CMakeFiles/nvd_response.dir/src/response-sample.cpp.o: CMakeFiles/nvd_response.dir/flags.make
CMakeFiles/nvd_response.dir/src/response-sample.cpp.o: ../src/response-sample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/Documents/NVD/NVDReqRes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nvd_response.dir/src/response-sample.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nvd_response.dir/src/response-sample.cpp.o -c /home/sdv-2534/Documents/NVD/NVDReqRes/src/response-sample.cpp

CMakeFiles/nvd_response.dir/src/response-sample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvd_response.dir/src/response-sample.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/Documents/NVD/NVDReqRes/src/response-sample.cpp > CMakeFiles/nvd_response.dir/src/response-sample.cpp.i

CMakeFiles/nvd_response.dir/src/response-sample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvd_response.dir/src/response-sample.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/Documents/NVD/NVDReqRes/src/response-sample.cpp -o CMakeFiles/nvd_response.dir/src/response-sample.cpp.s

# Object files for target nvd_response
nvd_response_OBJECTS = \
"CMakeFiles/nvd_response.dir/src/response-sample.cpp.o"

# External object files for target nvd_response
nvd_response_EXTERNAL_OBJECTS =

nvd_response: CMakeFiles/nvd_response.dir/src/response-sample.cpp.o
nvd_response: CMakeFiles/nvd_response.dir/build.make
nvd_response: /usr/local/lib/libvsomeip3.so.3.1.20
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
nvd_response: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
nvd_response: CMakeFiles/nvd_response.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdv-2534/Documents/NVD/NVDReqRes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nvd_response"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nvd_response.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nvd_response.dir/build: nvd_response

.PHONY : CMakeFiles/nvd_response.dir/build

CMakeFiles/nvd_response.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nvd_response.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nvd_response.dir/clean

CMakeFiles/nvd_response.dir/depend:
	cd /home/sdv-2534/Documents/NVD/NVDReqRes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdv-2534/Documents/NVD/NVDReqRes /home/sdv-2534/Documents/NVD/NVDReqRes /home/sdv-2534/Documents/NVD/NVDReqRes/build /home/sdv-2534/Documents/NVD/NVDReqRes/build /home/sdv-2534/Documents/NVD/NVDReqRes/build/CMakeFiles/nvd_response.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nvd_response.dir/depend

