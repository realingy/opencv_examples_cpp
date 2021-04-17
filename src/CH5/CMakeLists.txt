cmake_minimum_required(VERSION 3.5)

project(opencv_ch5)

include_directories(${CMAKE_SOURCE_DIR}/..)

set( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_CONFIGRATION_TYPES "Release" CACHE STRING "" FORCE)

set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/install/include)
include_directories(${OpenCV_DIR}/install/include/opencv)
include_directories(${OpenCV_DIR}/install/include/opencv2)

# aux_source_directory(. DIR_SRCS)

add_executable(1_accessPixel "accessPixel.cpp")
target_link_libraries (1_accessPixel ${OpenCV_LIBS})

add_executable(2_accessPixel "accessPixel2.cpp")
target_link_libraries (2_accessPixel ${OpenCV_LIBS})

add_executable(3_accessPixel "accessPixel3.cpp")
target_link_libraries (3_accessPixel ${OpenCV_LIBS})

add_executable(4_accessPixel "accessPixeln.cpp")
target_link_libraries (4_accessPixel ${OpenCV_LIBS})

add_executable(5_blend "blend.cpp")
target_link_libraries (5_blend ${OpenCV_LIBS})

add_executable(6_blendMultichannel "blendMultichannel.cpp")
target_link_libraries (6_blendMultichannel ${OpenCV_LIBS})

add_executable(7_bright "bright.cpp")
target_link_libraries (7_bright ${OpenCV_LIBS})

add_executable(8_dft "DFT.cpp")
target_link_libraries (8_dft ${OpenCV_LIBS})

add_executable(9_xml "xml.cpp")
target_link_libraries (9_xml ${OpenCV_LIBS})
