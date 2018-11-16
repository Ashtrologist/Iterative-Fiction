cmake_minimum_required(VERSION 3.12)
project(Iterative_Fiction)

set(CMAKE_CXX_STANDARD 14)

add_executable(Iterative_Fiction main.cpp, StoryTokenizer.cpp, StoryTokenizer.h)