cmake_minimum_required(VERSION 2.8)
project(GPS_REQ_RES)
set(CMAKE_CXX_FLAGS "-g -std=c++14")
find_package(vsomeip3 REQUIRED)
find_package(Boost 1.55 COMPONENTS system thread log REQUIRED)


include_directories(
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)


include_directories(include)
add_executable(request  ./src/GPS_Request_Sample.cpp)
add_executable(response ./src/GPS_Response_Sample.cpp)
target_link_libraries( request vsomeip3 ${Boost_LIBRARIES})
target_link_libraries( response vsomeip3 ${Boost_LIBRARIES})