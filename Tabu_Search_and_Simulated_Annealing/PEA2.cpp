//
// Created by Kuba on 02.12.2018.
//

#include "PEA2.h"
#include "Time.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <algorithm>

double stoper=60;
float delta=0.999997;

PEA2::PEA2():tabuSearch(travelingSalesman), simulatedAnnealing(travelingSalesman) {

}

PEA2::~PEA2() {

}

void PEA2::start() {

    int choice;
    while (true)
    {
        std::cout << "1. Wczytaj macierz " << std::endl;
        std::cout << "2. Wyswietl macierz ." << std::endl;
        std::cout << "3. Uruchom Tabu Search" << std::endl;
        std::cout << "4. Uruchom Simulated Annealing" << std::endl;
        std::cout << "5. Wprowadz wspolczynnik zmiany temperatury "<<std::endl;
        std::cout << "6. Wprowadz kryterium stopu "<<std::endl;
        std::cout << "7. Zakoncz ";
        std::cout << std::endl << "Wybierz opcje: ";

        std::cin >> choice;

        std::cout << std::endl << std::endl;

        switch (choice)
        {

            case 1:
                readMatrixFromFile();
                break;

            case 2:
                printMatrix();
                break;

            case 3:
                startTabuSearch();
                break;

            case 4:
                startSimulatedAnnealing();
                break;

            case 5:
                std::cout<<"Podaj wspolczynnik zmiany temperatury: "<<std::endl;
                std::cin>>delta;
                break;
            case 6:
                std::cout<<"Podaj kryterium stopu w sekundach: "<<std::endl;
                std::cin>>stoper;
                break;
            case 7:
                return;

            default:
                std::cout<<"Podano bledny znak"<<std::endl;
                break;
        }
    }
}

void PEA2::readMatrixFromKeyboard(){

    std::cout << "Podaj liczbe miast:\n";
    std::string cityNumbers;
    std::cin >> cityNumbers;

    int cost;
    int matrixSize = atoi(cityNumbers.c_str());

    travelingSalesman.setSize(matrixSize);

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (i != j)
            {

                std::cout << "Podaj koszt z miasta " << i << " do miasta " << j << "\t";
                std::cin >> cost;
                travelingSalesman.setCost(cost, i, j);

            }
        }
    }
}

void PEA2::readMatrixFromFile(){

    std::cout << "Podaj sciezke do pliku z macierza:\n";
    std::string filePath;
    std::cin >> filePath;

    if (travelingSalesman.fileToMatrix(filePath))
    {

        std::cout << "Wczytanie macierzy powiodlo sie.\n";

    }
    else
    {

        std::cout << "Wczytanie macierzy nie powiodlo sie: \n";

    }

}

void PEA2::printMatrix() {

    std::cout << std::endl << std::endl << travelingSalesman.getMatrixToString() << std::endl;

}

void PEA2::startTabuSearch() {

    //for (int i=0; i<10;i++) {
        tabuSearch.startTabuSearch(30, 800, 200, 20, stoper);
        std::cout << std::endl << tabuSearch.getSolutionToString(tabuSearch.bestSolution, tabuSearch.minCost)
                  << std::endl;
    //}
}

void PEA2::startSimulatedAnnealing() {

    //for(int i=0; i<10;i++) {

        simulatedAnnealing.startSimulatedAnnealing(delta, 10, 0.5, stoper);
        std::cout << std::endl
                  << simulatedAnnealing.getSolutionToString(simulatedAnnealing.bestSolution, simulatedAnnealing.minCost)
                  << std::endl;
    //}
}

void PEA2::startSimulatedAnnealingStepByStep() {

    simulatedAnnealing.startSimulatedAnnealingStepByStep();
    std::cout << std::endl << simulatedAnnealing.getSolutionToString(simulatedAnnealing.bestSolution, simulatedAnnealing.minCost) << std::endl;

}