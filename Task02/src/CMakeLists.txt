cmake_minimum_required(VERSION 3.16)
project(Task02)
add_executable(Task02 main.cpp)
target_link_libraries(Task02 ${OpenCV_LIBS})