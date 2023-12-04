cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -std=c++11")
project(prg1)
find_package(vsomeip3 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )
include_directories (
   ${Boost_INCLUDE_DIR}
   ${VSOMEIP_INCLUDE_DIRS}
)
include_directories(include)
add_executable(nvd_response ../src/response-sample.cpp)
target_link_libraries(nvd_response vsomeip3 ${Boost_LIBRARIES})

add_executable(nvd_request ../src/request-sample.cpp)
target_link_libraries(nvd_request vsomeip3 ${Boost_LIBRARIES})
