cmake_minimum_required(VERSION 3.5)

project(opencv_ch4)

# add_subdirectory()
set( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_CONFIGRATION_TYPES "Release" CACHE STRING "" FORCE)

set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/install/include)
include_directories(${OpenCV_DIR}/install/include/opencv)
include_directories(${OpenCV_DIR}/install/include/opencv2)

# aux_source_directory(. DIR_SRCS)

add_executable(01_draw "draw.cpp")
target_link_libraries(01_draw ${OpenCV_LIBS})

add_executable(02_mat "draw.cpp")
target_link_libraries(02_mat ${OpenCV_LIBS})
