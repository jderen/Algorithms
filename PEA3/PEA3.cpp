//
// Created by Kuba on 19.12.2018.
//

#include "PEA3.h"
#include "TravelingSalesman.h"
#include "GeneticAlgorithm.h"
#include <iostream>

PEA3::PEA3():geneticAlgorithm(travelingSalesman) {

}

PEA3::~PEA3() {

}

void PEA3::start() {

    int choice;
    while (true)
    {
        std::cout << "1. Wczytaj macierz " << std::endl;
        std::cout << "2. Wyswietl macierz ." << std::endl;
        std::cout << "3. Uruchom Genethic Algorithm" << std::endl;
        std::cout << "4. Ustaw wielkosc populacji poczatkowej" << std::endl;
        std::cout << "5. Ustaw wspolczynnik mutacji "<<std::endl;
        std::cout << "6. Wprowadz kryterium stopu "<<std::endl;
        std::cout << "7. Ustaw wspolczynnik krzyzowania "<<std::endl;
        std::cout << "8. Zakoncz ";
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
                startAlgorithm();
                break;

            case 4:
                std::cout<<"Podaj wielkosc populacji poczatkowej: "<<std::endl;
                //startSimulatedAnnealing();
                break;

            case 5:
                std::cout<<"Podaj wspolczynnik mutacji: "<<std::endl;
                //std::cin>>delta;
                break;
            case 6:
                std::cout<<"Podaj kryterium stopu w sekundach: "<<std::endl;
                //std::cin>>stoper;
                break;
            case 7:
                std::cout<<"Podaj wspolczynnik krzyzowania"<<std::endl;
                return;

            case 8:
                return;
            default:
                std::cout<<"Podano bledny znak"<<std::endl;
                break;
        }
    }
}


void PEA3::readMatrixFromFile(){

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

void PEA3::printMatrix() {

    std::cout << std::endl << std::endl << travelingSalesman.getMatrixToString() << std::endl;

}

void PEA3::startAlgorithm()
{
    geneticAlgorithm.startAlgorithm(90, 100, 0.35);
    std::cout << std::endl << geneticAlgorithm.getSolutionToString(geneticAlgorithm.best_solution, geneticAlgorithm.min_cost) << std::endl;

}