cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemos)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(00_show)
add_subdirectory(01_blur)
add_subdirectory(02_canny)
add_subdirectory(03_resize)
add_subdirectory(04_color)
add_subdirectory(05_GaussianBlur)
add_subdirectory(06_VideoOpen)
add_subdirectory(07_VideoCapture)
add_subdirectory(08_VideoCaptureCanny)
