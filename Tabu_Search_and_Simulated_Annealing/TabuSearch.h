//
// Created by Kuba on 02.12.2018.
//

#ifndef PEA2PROJECT_TABUSEARCH_H
#define PEA2PROJECT_TABUSEARCH_H

#include "TravelingSalesman.h"
#include <vector>
#include <string>
#include <list>

class TabuSearch {

private:
    TravelingSalesman& travelingSalesman;
    std::list<std::pair<int, int> > tabu_list;

    float countProbability(int current_cost, int new_cost, float current_temperature);
    int countCost(std::vector<int> path);

public:
    TabuSearch(TravelingSalesman& salesman);
    ~TabuSearch();

    int minCost;
    std::vector< int > bestSolution;

    std::vector <int> generateRandomSolution();
    std::string getSolutionToString(std::vector<int> path, int cost);
    std::pair<int, int> swapTwoRandomCities(std::vector<int>& path);
    void startTabuSearch(int tabu_list_size, int neighbours_count , int steps_without_change , int steps_with_random_neighbourhood ,double stoper);
    bool checkTabu(std::pair<int, int>&, std::vector<int>& path, int neighbour_cost);


};


#endif //PEA2PROJECT_TABUSEARCH_H
