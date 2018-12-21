cmake_minimum_required(VERSION 3.12)
project(PEA3)

set(CMAKE_CXX_STANDARD 14)

add_executable(PEA3 main.cpp PEA3.cpp PEA3.h TravelingSalesman.cpp TravelingSalesman.h GeneticAlgorithm.cpp GeneticAlgorithm.h)