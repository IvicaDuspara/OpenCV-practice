cmake_minimum_required(VERSION 3.16)
project(Task03)
add_executable(Task03 main.cpp)
target_link_libraries(Task03 ${OpenCV_LIBS})