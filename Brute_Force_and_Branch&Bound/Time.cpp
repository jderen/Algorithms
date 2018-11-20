//
// Created by Kuba on 08.11.2018.
//

#include "Time.h"
#include "RandomGenerator.h"
#include "TravellingSalesian.h"
#include <iostream>
#include <ctime>

Time::Time()
{
}

double Time::timeBruteForce(int cityNumbers, int howMany, RandomGenerator randomGenerator, bool isPrinting) {

    double * time = new double[howMany];

    for(int i = 0; i < howMany; i++)
    {
        randomGenerator.getTravellingSalesman(cityNumbers);

        //Creating new Travelling Salesman
        TravellingSalesian travellingSalesian;

        // Counting time
        clock_t start = clock();
        travellingSalesian.bruteForce(isPrinting);
        clock_t end = clock();

        //Obliczanie wyniku
        double fragmentaryTime = (end-start)*1000000/CLOCKS_PER_SEC;
        time[i] = fragmentaryTime;
    }

    // Variable do counting average time
    double fullTime = 0;

    for(int i = 0; i < howMany; i++)
    {
        fullTime += time[i];
    }
    delete [] time;
    return fullTime/howMany;
}

double Time::timeBranchAndBound(int cityNumbers, int howMany, RandomGenerator randomGenerator, bool isPrinting)
{
    double * time = new double[howMany];

    for(int i = 0; i < howMany; i++)
    {
        randomGenerator.getTravellingSalesman(cityNumbers);

        //Creating new Travelling Salesman
        TravellingSalesian travellingSalesian;

        // Counting time
        clock_t start = clock();
        travellingSalesian.branchAndBound(isPrinting);
        clock_t end = clock();

        // Counting result
        double fragmentaryTime = (end-start)*1000000/CLOCKS_PER_SEC;
        time[i] = fragmentaryTime;
    }

    // Variable do counting average time
    double fullTime = 0;

    for(int i = 0; i < howMany; i++)
    {
        fullTime += time[i];
    }
    delete [] time;
    return fullTime/howMany;
}