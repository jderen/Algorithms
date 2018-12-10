//
// Created by Kuba on 02.12.2018.
//

#ifndef PEA2PROJECT_PEA2_H
#define PEA2PROJECT_PEA2_H

#include "TravelingSalesman.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"

class PEA2 {

private:
    TabuSearch tabuSearch;
    TravelingSalesman travelingSalesman;
    SimulatedAnnealing simulatedAnnealing;

    void readMatrixFromFile();
    void readMatrixFromKeyboard();
    void printMatrix();
    void startTabuSearch();
    void startSimulatedAnnealing();
    void startSimulatedAnnealingStepByStep();

public:
    PEA2();
    ~PEA2();
    void start();


};


#endif //PEA2PROJECT_PEA2_H
