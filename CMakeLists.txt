cmake_minimum_required(VERSION 3.12)
project(Iterative_Fiction)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/ashtonrodriquez/Documents/Iterative-Fiction/cmake-build-debug")


add_executable(Iterative_Fiction main.cpp Passage.cpp Passage.h Command.cpp Command.h Display.cpp Display.h)