cmake_minimum_required(VERSION 3.5)

project(opencv_ch3)

include_directories(${CMAKE_SOURCE_DIR}/..)

set( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_CONFIGRATION_TYPES "Release" CACHE STRING "" FORCE)

set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/install/include)
include_directories(${OpenCV_DIR}/install/include/opencv)
include_directories(${OpenCV_DIR}/install/include/opencv2)

# aux_source_directory(. DIR_SRCS)

add_executable(01_imshow "show.cpp")
target_link_libraries (01_imshow ${OpenCV_LIBS})

add_executable(02_alphamat "alphamat.cpp")
target_link_libraries (02_alphamat ${OpenCV_LIBS})

add_executable(03_mouse "mouse.cpp")
target_link_libraries (03_mouse ${OpenCV_LIBS})

add_executable(04_trackbar "trackbar.cpp")
target_link_libraries (04_trackbar ${OpenCV_LIBS})
