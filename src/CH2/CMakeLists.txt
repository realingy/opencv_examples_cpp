cmake_minimum_required(VERSION 3.5)

project(opencv_ch2)

# add_subdirectory(01_ObjectTrace)

set( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_CONFIGRATION_TYPES "Release" CACHE STRING "" FORCE)

set(OpenCV_DIR $ENV{OPENCV_DIR})
# message(${OpenCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/install/include)
include_directories(${OpenCV_DIR}/install/include/opencv)
include_directories(${OpenCV_DIR}/install/include/opencv2)

# aux_source_directory(. DIR_SRCS)

add_executable(01_object_trace "objecttrace.cpp")
target_link_libraries (01_object_trace ${OpenCV_LIBS})

add_executable(02_object_detect "objectdetect.cpp")
target_link_libraries (02_object_detect ${OpenCV_LIBS})

add_executable(03_point_trace "pointtrace.cpp")
target_link_libraries (03_point_trace ${OpenCV_LIBS})
