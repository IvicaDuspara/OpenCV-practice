cmake_minimum_required(VERSION 3.16)
project(Task01)
set(CMAKE_CXX_STANDARD 20)
set(OpenCV_DIR "/usr/local/lib/opencv4/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

add_subdirectory("src" "bin")
