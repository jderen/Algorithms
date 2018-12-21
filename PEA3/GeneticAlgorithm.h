//
// Created by Kuba on 19.12.2018.
//

#ifndef PEA3_GENETICALGORITHM_H
#define PEA3_GENETICALGORITHM_H

#include "TravelingSalesman.h"
#include <string>
#include <vector>
#include <list>

class GeneticAlgorithm {

private:
    TravelingSalesman travelingSalesman;
    std::vector<std::pair<std::vector<int>, int> > population;


public:

    GeneticAlgorithm(TravelingSalesman& t);
    ~GeneticAlgorithm();
    std::vector< int > best_solution;
    int min_cost;

    void startAlgorithm(int population_size, int generation_count, float mutation_probability);
    std::vector <int> generateRandomSolution();
    int countCost(std::vector<int> path);
    void swapTwoRandomCities(std::vector<int>& path);
    bool isSolutionUnique(std::pair<std::vector<int>, int> new_solution, std::vector<std::pair<std::vector<int>, int> > population);
    std::vector<std::pair<std::vector<int>, int> > crossoverPMX(int population_size, float mutation_probability);
    void addCorrectCityAt(std::pair<std::vector<int>, int> &child, std::pair<std::vector<int>, int> const &parent, int position, int first, int second);
    void mutate(std::pair<std::vector<int>, int>& speciman, float probability);
    std::string getSolutionToString(std::vector<int> path, int cost);
};


#endif //PEA3_GENETICALGORITHM_H
