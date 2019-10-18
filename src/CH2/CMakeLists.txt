cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh2)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(01_ObjectTrace)
add_subdirectory(02_ObjectDetect)
add_subdirectory(03_PointTrace)

