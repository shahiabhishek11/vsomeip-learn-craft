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
CMAKE_SOURCE_DIR = /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build

# Include any dependencies generated for this target.
include CMakeFiles/camdata_notify.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/camdata_notify.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camdata_notify.dir/flags.make

CMakeFiles/camdata_notify.dir/src/notify.cpp.o: CMakeFiles/camdata_notify.dir/flags.make
CMakeFiles/camdata_notify.dir/src/notify.cpp.o: ../src/notify.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camdata_notify.dir/src/notify.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/camdata_notify.dir/src/notify.cpp.o -c /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/src/notify.cpp

CMakeFiles/camdata_notify.dir/src/notify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camdata_notify.dir/src/notify.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/src/notify.cpp > CMakeFiles/camdata_notify.dir/src/notify.cpp.i

CMakeFiles/camdata_notify.dir/src/notify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camdata_notify.dir/src/notify.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/src/notify.cpp -o CMakeFiles/camdata_notify.dir/src/notify.cpp.s

# Object files for target camdata_notify
camdata_notify_OBJECTS = \
"CMakeFiles/camdata_notify.dir/src/notify.cpp.o"

# External object files for target camdata_notify
camdata_notify_EXTERNAL_OBJECTS =

camdata_notify: CMakeFiles/camdata_notify.dir/src/notify.cpp.o
camdata_notify: CMakeFiles/camdata_notify.dir/build.make
camdata_notify: /usr/local/lib/libvsomeip3.so.3.3.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
camdata_notify: /usr/local/lib/libopencv_gapi.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_highgui.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_ml.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_objdetect.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_photo.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_stitching.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_video.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_videoio.so.4.8.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
camdata_notify: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
camdata_notify: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_dnn.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_calib3d.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_features2d.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_flann.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_imgproc.so.4.8.0
camdata_notify: /usr/local/lib/libopencv_core.so.4.8.0
camdata_notify: CMakeFiles/camdata_notify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable camdata_notify"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camdata_notify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camdata_notify.dir/build: camdata_notify

.PHONY : CMakeFiles/camdata_notify.dir/build

CMakeFiles/camdata_notify.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camdata_notify.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camdata_notify.dir/clean

CMakeFiles/camdata_notify.dir/depend:
	cd /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build /home/sdv-2534/Documents/SensorSharing/NVD_Notify_Subscribe/build/CMakeFiles/camdata_notify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camdata_notify.dir/depend

