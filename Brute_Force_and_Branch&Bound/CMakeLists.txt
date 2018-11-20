cmake_minimum_required(VERSION 3.12)
project(Asymmetric_Traveling_Salesian_Problem)

set(CMAKE_CXX_STANDARD 14)

add_executable(Asymmetric_Traveling_Salesian_Problem main.cpp RandomGenerator.cpp RandomGenerator.h TravellingSalesian.cpp TravellingSalesian.h Time.cpp Time.h)