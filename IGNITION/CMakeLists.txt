cmake_minimum_required (VERSION 2.8)
project(prg1)
set(CMAKE_CXX_FLAGS "-g -std=c++11")

find_package(vsomeip3 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
   ${Boost_INCLUDE_DIR}
   ${VSOMEIP_INCLUDE_DIRS}
   
)

include_directories(include)
add_executable(ignition ../src/notify-ignition.cpp)
target_link_libraries(ignition vsomeip3 ${Boost_LIBRARIES})