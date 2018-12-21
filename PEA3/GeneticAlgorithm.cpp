//
// Created by Kuba on 19.12.2018.
//

#include "GeneticAlgorithm.h"
#include <iostream>
#include <ctime>
#include <limits>
#include <algorithm>

// constructor
GeneticAlgorithm::GeneticAlgorithm(TravelingSalesman& t) : travelingSalesman(t)
{

}

// destructor
GeneticAlgorithm::~GeneticAlgorithm()
{

}

// return true if solution first is better than solution second
struct PathComparator {

    bool operator() (std::pair<std::vector<int>, int> first, std::pair<std::vector<int>, int> second)
    {

        return (first.second < second.second);

    }

};

// starting algorithm
void GeneticAlgorithm::startAlgorithm(int population_size, int generation_count, float mutation_probability)
{
    srand(time(NULL));

    std::pair<std::vector<int>, int> first_solution, new_solution;
    population.clear();

    // first solution is random
    first_solution.first = generateRandomSolution();
    first_solution.second = countCost(first_solution.first);
    population.push_back(first_solution);


    // at the beginning population gets solutions from neighboorhood of type swap first random solution
    for (int i = 1; i < population_size; i++)
    {

        new_solution.first = first_solution.first;
        swapTwoRandomCities(new_solution.first);
        new_solution.second = countCost(new_solution.first);

        // population getting only unique solutions
        if (isSolutionUnique(new_solution, population))
        {

            population.push_back(new_solution);

        }

        else
        {

            i--;

        }
    }

    PathComparator pathComparator;

    // sorting solution from best to worst
    std::sort(population.begin(), population.end(), pathComparator);

    std::vector<std::pair<std::vector<int>, int> > next_generation;

    // evolution population through counting amount of generations
    for (int i = 0; i < generation_count; i++)
    {

        // next geneteration setting by crossover type PMX
        next_generation = crossoverPMX(population_size, mutation_probability);

        // to the population adding best solutions from old generation and a new generation
        population.insert(population.end(), next_generation.begin(), next_generation.end());
        std::sort(population.begin(), population.end(), pathComparator);
        population.resize(population_size);

    }

    best_solution = population[0].first;
    min_cost = population[0].second;

}

// random permutation of cities
std::vector <int> GeneticAlgorithm::generateRandomSolution()
{
    std::vector <int> solution;
    for (int i = 0; i < travelingSalesman.getSize(); i++)
    {

        solution.push_back(i);

    }

    std::random_shuffle(solution.begin(), solution.end());
    return solution;

}

// counting cost of path
int GeneticAlgorithm::countCost(std::vector<int> path)
{
    int cost = 0;

    for (std::size_t i = 0; i < path.size() - 1; i++)
    {

        cost += travelingSalesman.getCost(path[i], path[i + 1]);

    }

    cost += travelingSalesman.getCost(path[path.size() - 1], path[0]);
    return cost;
}

// swapping positions of two cities
void GeneticAlgorithm::swapTwoRandomCities(std::vector<int>& path)
{

    int firstPosition = rand() % path.size();
    int secondPosition;

    do {
        secondPosition = rand() % path.size();
    } while (firstPosition == secondPosition);

    int buffor = path.at(firstPosition);
    path.at(firstPosition) = path.at(secondPosition);
    path.at(secondPosition) = buffor;

}

//sprawdzenie czy dane rozwi¹zanie jest unikalne

bool GeneticAlgorithm::isSolutionUnique(std::pair<std::vector<int>, int> new_solution, std::vector<std::pair<std::vector<int>, int> > population)
{
    for (std::pair<std::vector<int>,int> solution : population)
    {
        // another cost so another solutions
        if (new_solution.second == solution.second)
        {
            // setting together start of permutation
            int common_begin = 0;

            while (new_solution.first[0] != solution.first[common_begin])
            {

                common_begin++;

            }

            int index = 0;
            int equal_cities = 0;

            for (int i = 0; i < new_solution.first.size(); i++)
            {

                index = (common_begin + i) % new_solution.first.size();

                // counting together cities in a path
                if (new_solution.first[i] == solution.first[index])
                {

                    equal_cities++;

                }
                else
                    break;
            }
            // if all cities are the same solution is not unique
            if (equal_cities == new_solution.first.size())
            {

                return false;

            }
        }
    }

    return true;

}

// counting new generation
std::vector<std::pair<std::vector<int>, int> > GeneticAlgorithm::crossoverPMX(int population_size, float mutation_probability)
{

    std::vector<std::pair<std::vector<int>, int> > next_generation;
    std::pair<std::vector<int>, int> first_parent, second_parent, first_child, second_child;

    int first_cross_point, second_cross_point;

    // new generation is not smaller than population
    while (next_generation.size() < population_size)
    {
        // choosing pair solutions methods of roulette to crossing
        first_parent = population[rand()%population.size()];
        second_parent = population[rand() % population.size()];


        // all places in paths of potomstwo filling by -1, the city cant have this number
        first_child.first.resize(travelingSalesman.getSize(), -1);
        second_child.first.resize(travelingSalesman.getSize(), -1);

        // randomly choosed places to crossing
        first_cross_point = rand() % travelingSalesman.getSize();

        do
        {
            second_cross_point = rand() % travelingSalesman.getSize();

        } while (first_cross_point == second_cross_point);

        // first cross point must be near beginning of vector
        if (first_cross_point > second_cross_point)
        {

            int buffor = first_cross_point;
            first_cross_point = second_cross_point;
            second_cross_point = buffor;

        }

        // to potomków getting by cross areas of crossing
        for (int j = first_cross_point; j <= second_cross_point; j++)
        {

            first_child.first[j] = second_parent.first[j];
            second_child.first[j] = first_parent.first[j];

        }

        // filling rest of path
        for (int j = 0; j < travelingSalesman.getSize(); j++)
        {
            // pomijam area of crossing
            if (j == first_cross_point)
            {

                j = second_cross_point;
                continue;

            }

            // adding the city at j position
            addCorrectCityAt(first_child, first_parent, j, first_cross_point, second_cross_point);

            addCorrectCityAt(second_child, second_parent, j, first_cross_point, second_cross_point);

        }

        // mutations of potomków are with setting propability
        mutate(first_child, mutation_probability);
        mutate(second_child, mutation_probability);


        // to next generation adding only solutions not being in this generation and parent generation
        first_child.second = countCost(first_child.first);
        second_child.second = countCost(second_child.first);

        //if (solutionIsUnique(first_child, next_generation) && solutionIsUnique(first_child, population)) next_generation.push_back(first_child);
        //if (solutionIsUnique(second_child, next_generation) && solutionIsUnique(second_child, population)) next_generation.push_back(second_child);

        next_generation.push_back(first_child);
        next_generation.push_back(second_child);
        first_child.first.clear();
        second_child.first.clear();

    }

    return next_generation;

}

void GeneticAlgorithm::addCorrectCityAt(std::pair<std::vector<int>, int> &child, std::pair<std::vector<int>, int> const &parent, int position, int first, int second)
{
    // pointer of moving in the area of crossing
    int shift = 0;

    //szerokoœæ przedzia³u krzy¿owania
    int interval = second - first + 1;

    // checking if element which must be added is not in a solution(was in area of crossing)
    int found_index = std::find(child.first.begin(),
                                child.first.end(),
                                parent.first[position])
                      - child.first.begin();

    // if element is not found in a path
    if (found_index == child.first.size())
    {

        child.first[position] = parent.first[position];

    }

    else
    {

        // setting element, which should be added from the area of crossing of second osobnik
        while (std::find(child.first.begin(), child.first.end(), parent.first[first + (found_index - first + shift) % interval])
               != child.first.end())
        {
            shift++;
        }

        child.first[position] = parent.first[first + (found_index - first + shift) % interval];
    }
}

// mutation of solution
void GeneticAlgorithm::mutate(std::pair<std::vector<int>, int>& speciman, float probability)
{

    // if it is wylosowane propability less than setting do a mutation
    if ((float)rand() / RAND_MAX < probability)
    {

        // wylosowana amount of ruchow swap in a mutation/ maximum is population_size/4
        int swap_number = rand() % population.size()/4;

        for (int i = 0; i <= swap_number; i++)
        {

            swapTwoRandomCities(speciman.first);

        }
    }
}

std::string GeneticAlgorithm::getSolutionToString(std::vector<int> path, int cost) {

    std::string str = "";
    str.append("Koszt przejscia sciezki:\n");
    str.append(std::to_string(cost));
    str.append("\nSciezka:\n");

    for (std::size_t i = 0; i < path.size(); i++)
    {

        str.append(std::to_string(path[i]));
        str.append(" ");

    }

    return str;

}