cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh9)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(1_H-S-Histogram)
add_subdirectory(2_Histogram2)
add_subdirectory(3_histogram3)
add_subdirectory(4_compareHist)
add_subdirectory(5_calcBackProject)
add_subdirectory(6_matchTemplate)
