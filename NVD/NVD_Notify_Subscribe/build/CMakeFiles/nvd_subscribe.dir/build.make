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
CMAKE_SOURCE_DIR = /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build

# Include any dependencies generated for this target.
include CMakeFiles/nvd_subscribe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nvd_subscribe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nvd_subscribe.dir/flags.make

CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o: CMakeFiles/nvd_subscribe.dir/flags.make
CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o: ../src/subscribe.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o -c /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/src/subscribe.cpp

CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/src/subscribe.cpp > CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.i

CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/src/subscribe.cpp -o CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.s

# Object files for target nvd_subscribe
nvd_subscribe_OBJECTS = \
"CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o"

# External object files for target nvd_subscribe
nvd_subscribe_EXTERNAL_OBJECTS =

nvd_subscribe: CMakeFiles/nvd_subscribe.dir/src/subscribe.cpp.o
nvd_subscribe: CMakeFiles/nvd_subscribe.dir/build.make
nvd_subscribe: /usr/local/lib/libvsomeip3.so.3.3.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
nvd_subscribe: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
nvd_subscribe: CMakeFiles/nvd_subscribe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nvd_subscribe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nvd_subscribe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nvd_subscribe.dir/build: nvd_subscribe

.PHONY : CMakeFiles/nvd_subscribe.dir/build

CMakeFiles/nvd_subscribe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nvd_subscribe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nvd_subscribe.dir/clean

CMakeFiles/nvd_subscribe.dir/depend:
	cd /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build /home/sdv-2534/Documents/VSOMEIP_CODES/NVD/NVD_Notify_Subscribe/build/CMakeFiles/nvd_subscribe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nvd_subscribe.dir/depend

