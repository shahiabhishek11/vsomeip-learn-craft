cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -std=c++11")
project(CameraData)
find_package(vsomeip3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost 1.55 COMPONENTS system thread log REQUIRED)
include_directories(
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

include_directories(include)
add_executable(camdata_notify ../src/notify.cpp)
target_link_libraries(camdata_notify vsomeip3 ${Boost_LIBRARIES} ${OpenCV_LIBS})

add_executable(camdata_subscribe ../src/subscribe.cpp)
target_link_libraries(camdata_subscribe vsomeip3 ${Boost_LIBRARIES} ${OpenCV_LIBS})

