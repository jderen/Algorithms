//
// Created by Kuba on 08.11.2018.
//

#ifndef ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TIME_H
#define ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TIME_H
#include "RandomGenerator.h"

class Time {

public:
    Time();
    double timeBruteForce(int cityNumbers, int howMany, RandomGenerator randomGenerator, bool isPrinting);
    double timeBranchAndBound(int cityNumbers, int howMany, RandomGenerator randomGenerator, bool isPrinting);
};


#endif //ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TIME_H
