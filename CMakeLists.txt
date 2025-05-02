cmake_minimum_required(VERSION 3.30)
project(untitled4)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled4 main.cpp
        Design.cpp
       Design.h
        database.cpp
        database.h
        func.cpp
        func.h
        Room_se.cpp
        Room_se.h)
target_link_libraries(untitled4 odbc32)
