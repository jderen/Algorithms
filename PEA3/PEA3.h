//
// Created by Kuba on 19.12.2018.
//

#ifndef PEA3_PEA3_H
#define PEA3_PEA3_H

#include "TravelingSalesman.h"
#include "GeneticAlgorithm.h"


class PEA3 {

public:

    PEA3();
    ~PEA3();
    void start();


private:

    TravelingSalesman travelingSalesman;
    GeneticAlgorithm geneticAlgorithm;
    void readMatrixFromFile();
    void printMatrix();
    void startAlgorithm();
};


#endif //PEA3_PEA3_H
