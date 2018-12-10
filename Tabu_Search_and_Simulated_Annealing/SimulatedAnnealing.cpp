//
// Created by Kuba on 03.12.2018.
//

#include "SimulatedAnnealing.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>

// constructor
SimulatedAnnealing::SimulatedAnnealing(TravelingSalesman& salesman) : travelingSalesman(salesman) {

}

// destructor
SimulatedAnnealing::~SimulatedAnnealing() {

}

// starting simulated annealing
void SimulatedAnnealing::startSimulatedAnnealing(float _delta, int _itr_for_one_temp, float _final_temperature, double stoper) {

    clock_t end;
    clock_t endBest;
    clock_t bestTime;
    double totalTime=0;

    // starting timer
    clock_t start = clock();

    if (travelingSalesman.getSize() == 0) return;

    srand(time(NULL));

    int current_cost;
    int new_cost;


    // first solution randomly
    std::vector <int> current_solution(generateRandomSolution());
    current_cost = countCost(current_solution);


    std::vector <int> new_solution;

    float current_temperature;
    float delta = 0;
    float temp_delta;


    // setting start temperature
    for (int i = 1; i < std::pow(travelingSalesman.getSize(), 2); i++)
    {

        new_solution = generateRandomSolution();
        new_cost = countCost(new_solution);
        temp_delta = new_cost - current_cost;

        if (temp_delta > delta)
        {

            delta = temp_delta;

        }

        current_solution = new_solution;
        current_cost = new_cost;

    }

    // startint temperature
    current_temperature = delta;
    // delta
    delta = _delta;

    bestSolution = current_solution;
    minCost = current_cost;

    while (current_temperature > _final_temperature && totalTime<stoper )
    {
        for (int i = 0; i <_itr_for_one_temp; i++){

            new_solution = current_solution;
            swapTwoRandomCities(new_solution);
            new_cost = countCost(new_solution);
            if (new_cost < current_cost)
            {

                current_solution = new_solution;
                current_cost = new_cost;

                // saving best cost and solution
                if (new_cost < minCost)
                {

                    bestSolution = new_solution;
                    minCost = new_cost;

                    // kryterium stopu
                    endBest=clock();
                    bestTime=(endBest-start)*1/CLOCKS_PER_SEC;

                }
            }

            else
            {
                // random value in range [0,1]
                float r = float(rand() % 101) / 100.0f;

                // counting propability
                float p = countProbability(current_cost, new_cost, current_temperature);

                if (r < p)
                {

                    current_solution = new_solution;
                    current_cost = new_cost;

                }
            }
        }

        // cool down, current temperature is a new current temperature
        current_temperature *= delta;

        end = clock();
        totalTime=(end-start)/CLOCKS_PER_SEC;


    }

    // getting full time
    end = clock();
    double time=(end-start)*1/CLOCKS_PER_SEC;
    std::cout<<"Czas wykonywania: "<<time<<" s"<<std::endl;
    std::cout<<"Najlepsze rozwiazanie: "<<bestTime<<" s"<<std::endl;
}

std::vector <int> SimulatedAnnealing::generateRandomSolution() {

    std::vector <int> solution;

    for (int i = 0; i < travelingSalesman.getSize(); i++)
    {

        solution.push_back(i);

    }

    std::random_shuffle(solution.begin(), solution.end());

    return solution;
}

int SimulatedAnnealing::countCost(std::vector<int> path) {

    int cost = 0;

    for (std::size_t i = 0; i < path.size() - 1; i++)
    {

        cost += travelingSalesman.getCost(path[i], path[i + 1]);

    }

    cost += travelingSalesman.getCost(path[path.size() - 1], path[0]);

    return cost;
}

void SimulatedAnnealing::swapTwoRandomCities(std::vector<int>& path) {

    int firstPosition = rand() % path.size();
    int secondPosition;

    do {

        secondPosition = rand() % path.size();

    }while(firstPosition == secondPosition);

    int buffor = path[firstPosition];
    path[firstPosition] = path[secondPosition];
    path[secondPosition] = buffor;

}

float SimulatedAnnealing::countProbability(int current_cost, int new_cost, float current_temperature) {

    return powf(2.7182818f, -(float(new_cost - current_cost) / current_temperature));

}

std::string SimulatedAnnealing::getSolutionToString(std::vector<int> path, int cost)
{

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


void SimulatedAnnealing::startSimulatedAnnealingStepByStep() {

    if (travelingSalesman.getSize() == 0) return;

    srand(time(NULL));

    int current_cost;
    int new_cost;

    //std::cout << std::endl << "Wyznaczenie pierwszego rozwi¹zania przez losowanie...." << std::endl;

    std::vector <int> current_solution(generateRandomSolution());
    current_cost = countCost(current_solution);
    bestSolution = current_solution;
    minCost = current_cost;

    //std::cout << std::endl << getSolutionToString(current_solution, current_cost) << std::endl;

    std::vector <int> new_solution;

    float current_temperature;
    float delta = 0;
    float temp_delta;

    //std::cout << std::endl << "Wyznaczenie temperatury poczatkowej...." << std::endl;

    for (int i = 1; i < std::pow(travelingSalesman.getSize(), 2); i++)
    {

        new_solution = generateRandomSolution();
        new_cost = countCost(new_solution);
        temp_delta = new_cost - current_cost;

        if (temp_delta > delta)
        {

            delta = temp_delta;

        }

        current_solution = new_solution;
        current_cost = new_cost;
    }

    current_temperature = delta;
    delta = 0.999f;

    //std::cout << std::endl << "Temperatura poczatkowa: " << current_temperature << std::endl;
    //std::cout << std::endl << "Wspolczynnik schladzania: " << delta << std::endl;

    float end_temperature = 0.5f;

    //std::cout << std::endl << "Temperatura koncowa: " << end_temperature << std::endl;

    while (current_temperature > end_temperature) {

        new_solution = current_solution;
        swapTwoRandomCities(new_solution);
        new_cost = countCost(new_solution);

        //std::cout << std::endl << "Nowe rozwiazanie: ";
        //std::cout << std::endl << getSolutionToString(new_solution, new_cost) << std::endl;

        if (new_cost < current_cost) {

            current_solution = new_solution;
            current_cost = new_cost;

            if (new_cost < minCost)
            {

                bestSolution = new_solution;
                minCost = new_cost;

            }
        }
        else
        {

            float r = float(rand() % 101) / 100.0f;
            //std::cout << std::endl << "Losowa liczba z przedzialu [0,1]: ";
            //std::cout << std::endl << r << std::endl;

            float p = countProbability(current_cost, new_cost, current_temperature);

            //std::cout << std::endl << "Wartosc prawdopodobienstwa: ";
            //std::cout << std::endl << p << std::endl;

            if (r < p)
            {

                current_solution = new_solution;
                current_cost = new_cost;

            }

        }

        //std::cout << std::endl << "Aktualnie najlepsze rozwiazanie:";
        //std::cout << std::endl << getSolutionToString(current_solution, current_cost) << std::endl;
        //std::cout << std::endl << "Schladzanie..." << std::endl;

        current_temperature *= delta;

        //std::cout << std::endl << "Aktualna temperatura: " << current_temperature << std::endl;
        //std::cout << minCost << std::endl;

    }

    //std::cout << std::endl << "Najlepsze rozwiazanie:";
    //std::cout << std::endl << getSolutionToString(bestSolution, minCost) << std::endl;
}