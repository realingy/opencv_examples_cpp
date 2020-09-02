cmake_minimum_required(VERSION 3.5)

project(opencv_ch1)

set( CMAKE_CXX_FLAGS "-std=c++11" )

set(CMAKE_CONFIGRATION_TYPES "Release" CACHE STRING "" FORCE)

set(OpenCV_DIR $ENV{OPENCV_DIR})
# message(${OpenCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/install/include)
include_directories(${OpenCV_DIR}/install/include/opencv)
include_directories(${OpenCV_DIR}/install/include/opencv2)

# aux_source_directory(. DIR_SRCS)

add_executable(00_show "show.cpp")
target_link_libraries (00_show ${OpenCV_LIBS})

add_executable(01_blur "blur.cpp")
target_link_libraries (01_blur ${OpenCV_LIBS})

add_executable(02_canny "canny.cpp")
target_link_libraries (02_canny ${OpenCV_LIBS})

add_executable(03_resize "resize.cpp")
target_link_libraries (03_resize ${OpenCV_LIBS})

add_executable(04_color "color.cpp")
target_link_libraries (04_color ${OpenCV_LIBS})

add_executable(05_gaussianblur "gaussianblur.cpp")
target_link_libraries (05_gaussianblur ${OpenCV_LIBS})

add_executable(06_video "open.cpp")
target_link_libraries (06_video ${OpenCV_LIBS})

add_executable(07_videocapture "videocapture.cpp")
target_link_libraries (07_videocapture ${OpenCV_LIBS})

add_executable(08_videocapturecanny "videocapturecanny.cpp")
target_link_libraries (08_videocapturecanny ${OpenCV_LIBS})
