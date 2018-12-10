//
// Created by Kuba on 03.12.2018.
//

#ifndef PEA2PROJECT_SIMULATEDANNEALING_H
#define PEA2PROJECT_SIMULATEDANNEALING_H

#include "TravelingSalesman.h"
#include <vector>
#include <string>

class SimulatedAnnealing {

private:

    TravelingSalesman& travelingSalesman;

    int countCost(std::vector<int> path);
    float countProbability(int current_cost, int new_cost, float current_temperature);

public:

    SimulatedAnnealing(TravelingSalesman& salesman);
    ~SimulatedAnnealing();

    std::vector< int > bestSolution;
    int minCost;

    void startSimulatedAnnealing(float _delta, int _itr_for_one_temp, float _final_temperature, double stoper);
    void swapTwoRandomCities(std::vector<int>& path);
    std::vector <int> generateRandomSolution();
    std::string getSolutionToString(std::vector<int> path, int cost);
    void startSimulatedAnnealingStepByStep();

};


#endif //PEA2PROJECT_SIMULATEDANNEALING_H
