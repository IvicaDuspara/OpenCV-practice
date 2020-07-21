cmake_minimum_required(VERSION 3.16)
project(Task01)

add_executable(Task01 main.cpp)
target_link_libraries(Task01 ${OpenCV_LIBS})