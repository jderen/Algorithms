//
// Created by Kuba on 02.12.2018.
//

#include "TabuSearch.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(TravelingSalesman& salesman) : travelingSalesman(salesman) {

}

TabuSearch::~TabuSearch() {

}

// starting tabu search
void TabuSearch::startTabuSearch(int tabu_list_size, int neighbours_count, int steps_without_change, int steps_with_random_neighbourhood, double stoper) {

    clock_t end;
    clock_t endBest;
    clock_t bestTime;
    double totalTime;

    // starting timer
    clock_t start = clock();

    if (travelingSalesman.getSize() == 0) return;

    srand(static_cast<unsigned int>(time(NULL)));
    int current_cost;

    // generate random solution to start
    std::vector <int> current_solution(generateRandomSolution());
    current_cost = countCost(current_solution);

    bestSolution = current_solution;
    minCost = current_cost;

    std::pair<int, int> swaped_cities;
    std::pair<int, int> saved_swap;

    std::vector <int> the_best_neighbour;
    std::vector <int> neighbour;

    int neighbour_cost;
    int the_best_neighbour_cost;
    int steps = 0;
    int change_neighbourhood_count = 0;

    do {

        the_best_neighbour_cost = std::numeric_limits<int>::max();

        for (int i = 0; i < neighbours_count; i++)
        {
            neighbour = current_solution;
            swaped_cities = swapTwoRandomCities(neighbour);
            neighbour_cost = countCost(neighbour);

            if (neighbour_cost < the_best_neighbour_cost && checkTabu(swaped_cities, neighbour, neighbour_cost))
            {

                the_best_neighbour_cost = neighbour_cost;
                the_best_neighbour = neighbour;
                saved_swap = swaped_cities;

            }
        }

        current_solution = the_best_neighbour;
        current_cost = the_best_neighbour_cost;

        if (current_cost < minCost)
        {

            bestSolution = current_solution;
            minCost = current_cost;
            steps = 0;
            endBest=clock();
            bestTime=(endBest-start)*1/CLOCKS_PER_SEC;

        }

        if (tabu_list.size() > tabu_list_size)
        {

            tabu_list.pop_front();

        }

        tabu_list.push_back(saved_swap);
        steps++;

        // generate new random solution if too many repeat without change
        // critical event
        if (steps > steps_without_change)
        {

            current_solution = generateRandomSolution();
            current_cost = countCost(current_solution);
            change_neighbourhood_count++;
            steps = 0;

        }

        // getting full time
        end = clock();
        totalTime=(end-start)/CLOCKS_PER_SEC;

    } while (/*change_neighbourhood_count < steps_with_random_neighbourhood &&*/ totalTime<stoper );

    std::cout<<"Czas wykonywania: "<<totalTime<<" s"<<std::endl;
    std::cout<<"Najlepsze rozwiazanie: "<<bestTime<<" s"<<std::endl;
}

// generate random solution
std::vector <int> TabuSearch::generateRandomSolution() {

    std::vector <int> solution;
    for (int i = 0; i < travelingSalesman.getSize(); i++)
    {
        solution.push_back(i);
    }

    // generate random vector
    std::random_shuffle(solution.begin(), solution.end());

    return solution;

}

// counting edges costs
int TabuSearch::countCost(std::vector<int> path) {

    int cost = 0;

    for (std::size_t i = 0; i < path.size() - 1; i++)
    {

        cost += travelingSalesman.getCost(path[i], path[i + 1]);

    }

    cost += travelingSalesman.getCost(path[path.size() - 1], path[0]);

    return cost;

}

// swapping two random cities
std::pair<int, int> TabuSearch::swapTwoRandomCities(std::vector<int>& path) {

    int firstPosition = rand() % path.size();
    int secondPosition;

    // second position should be another than first position
    do {

        secondPosition = rand() % path.size();

    }while (firstPosition == secondPosition);

    std::pair<int, int> swaped_cities;

    if (firstPosition > secondPosition)
    {

        swaped_cities.first = path.at(secondPosition);
        swaped_cities.second = path.at(firstPosition);

    }

    else
    {

        swaped_cities.first = path.at(firstPosition);
        swaped_cities.second = path.at(secondPosition);

    }

    // swapping with using temporary buffor
    int buffor = path.at(firstPosition);
    path.at(firstPosition) = path.at(secondPosition);
    path.at(secondPosition) = buffor;

    return swaped_cities;
}

// checking tabu
bool TabuSearch::checkTabu(std::pair<int, int>& swaped_cities, std::vector<int>& path, int neighbour_cost) {

    // iterator for tabu list
    std::list<std::pair<int, int> >::iterator list_iterator = tabu_list.begin();

    while (list_iterator != tabu_list.end())
    {
        if (swaped_cities.first == list_iterator->second || swaped_cities.second == list_iterator->first)
        {

            int first_element_index = std::find(path.begin(), path.end(), list_iterator->first) - path.begin();
            int second_element_index = std::find(path.begin(), path.end(), list_iterator->second) - path.begin();
            // aspiration
            if (first_element_index < second_element_index && neighbour_cost > minCost) return false;

        }

        list_iterator++;
    }

    return true;

}

std::string TabuSearch::getSolutionToString(std::vector<int> path, int cost) {

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