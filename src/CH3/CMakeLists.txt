cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh3)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(01_imshow)
add_subdirectory(02_CreateMat)
add_subdirectory(03_mouse)
add_subdirectory(04_trackbar)
