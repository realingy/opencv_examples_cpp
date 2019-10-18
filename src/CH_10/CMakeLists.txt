cmake_minimum_required(VERSION 3.5)

# 工程信息
project(OpenCVDemosCh10)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(1_cornerHarris)
add_subdirectory(2_cornerHarris2)
add_subdirectory(3_goodFeaturesToTrack)
add_subdirectory(4_cornerSubPix)

