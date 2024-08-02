cmake_minimum_required(VERSION 3.27)
project(3530project3)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(matplotplusplus)

add_executable(3530project3
        main.cpp
        read.h
        )
target_link_libraries(3530project3 PUBLIC matplot)
