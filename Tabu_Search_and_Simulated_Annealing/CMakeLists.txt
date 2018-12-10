cmake_minimum_required(VERSION 3.12)
project(PEA2Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(PEA2Project main.cpp PEA2.cpp PEA2.h TravelingSalesman.cpp TravelingSalesman.h TabuSearch.cpp TabuSearch.h Time.cpp Time.h SimulatedAnnealing.cpp SimulatedAnnealing.h)