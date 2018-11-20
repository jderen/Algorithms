//
// Created by Kuba on 06.11.2018.
//


#ifndef ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TRAVELLINGSALESIAN_H
#define ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TRAVELLINGSALESIAN_H
#include <string>
#include <vector>

// struct representing a single node in a search Tree
struct node {

    // level of a tree
    int level;
    // temporary path from root
    std::vector <int> path;
    // counted bound using restriction function
    int bound;
};

// temporary struct using to place struct node in priority queue
struct nodeCompare {

    bool operator()(node a, node b) {
        return a.bound > b.bound;
    }
};


class TravellingSalesian {

private:
    int** matrix;
    int* bestBruteForce;
    int cityNumbers;
    int bestCost;


public:
    TravellingSalesian();
    ~TravellingSalesian();
    TravellingSalesian(std::string data);
    TravellingSalesian(int** matrix, int cityNumbers);
    void showMatrix();
    void bruteForce(bool isPrinting);
    void permutation(int T[], int ix);
    void swap(int &a, int &b);
    int costBruteForce(int array[]);
    void branchAndBound(bool isPrinting);
    int bottomBound(node a);
    int length(node a);
    bool check(node a, int i);
    bool check2(node a, int i);

};


#endif //ASYMMETRIC_TRAVELING_SALESIAN_PROBLEM_TRAVELLINGSALESIAN_H
