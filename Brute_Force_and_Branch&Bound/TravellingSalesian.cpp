//
// Created by Kuba on 06.11.2018.
//

#include "TravellingSalesian.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <climits>


// Constructor
TravellingSalesian::TravellingSalesian(){

    // Opening file to load data
    std::fstream file;
    file.open("dane", std::ios::in);

    if (file.is_open()) {

        // Loading numbers of city
        file >> cityNumbers;

        // Allocation memory for adjacency matrix
        matrix = new int*[cityNumbers];

        for (int i = 0; i < cityNumbers; i++) {

            matrix[i] = new int[cityNumbers];

            for (int j = 0; j < cityNumbers; j++) {
                file >> matrix[i][j];
            }
        }

        // Closing file with data
        file.close();
        // Array of cost
        bestBruteForce = new int[cityNumbers];
        // Best cost for brute force
        bestCost = INT_MAX;
        std::cout << "Dane z pliku " << "dane" << " zostały odczytane";
    }
    else {
        std::cout << "Brak pliku o takiej nazwie";
    }

    std::cout << std::endl << std::endl;
}

// Destructor
TravellingSalesian::~TravellingSalesian() {

    if (matrix!= NULL) {

        for (int i = 0; i < cityNumbers; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;
        matrix = NULL;
    }

    if (bestBruteForce != NULL) {
        delete[] bestBruteForce;
    }
}

// Constructor
TravellingSalesian::TravellingSalesian(std::string data) : matrix(NULL), bestBruteForce(NULL) {

    // Opening file to load data
    std::fstream file;
    file.open(data, std::ios::in);

    if (file.is_open()) {

        // Loading numbers of city
         file >> cityNumbers;

        // Allocation memory for adjacency matrix
        matrix = new int*[cityNumbers];

        for (int i = 0; i < cityNumbers; i++) {

            matrix[i] = new int[cityNumbers];

            for (int j = 0; j < cityNumbers; j++) {
                file >> matrix[i][j];
            }
        }

        // Closing file with data
        file.close();
        // Array of cost
        bestBruteForce = new int[cityNumbers];
        // Best cost for brute force
        bestCost = INT_MAX;
        std::cout << "Dane z pliku " << data << " zostały odczytane";
    }
    else {
        std::cout << "Brak pliku o takiej nazwie";
    }

    std::cout << std::endl << std::endl;
}

// Constructor
TravellingSalesian::TravellingSalesian(int ** matrix, int cityNumbers){

    this->matrix = matrix;
    this->cityNumbers = cityNumbers;
}

// Display loaded data
void TravellingSalesian::showMatrix() {

    if (matrix != NULL) {

        for (int i = 0; i < cityNumbers; i++) {
            for (int j = 0; j < cityNumbers; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "Brak danych do wyświetlenia" << std::endl;
    }
}

// Finding best way using brute force and display best permutation and its cost
void TravellingSalesian::bruteForce(bool isPrinting) {

    int* array = new int[cityNumbers];

    for (int i = 0; i < cityNumbers; i++) {

        array[i] = i;
    }

    permutation(array, 0);

    if (isPrinting) {

        std::cout << std::endl << std::endl << "Przeglad Zupelny" << std::endl;
        std::cout << "Sciezka = ";

        for (int i = 0; i < cityNumbers; i++) {

            if (i != 0) std::cout << " - ";
            std::cout << bestBruteForce[i];
        }
        std::cout << " - " << bestBruteForce[0] << std::endl;

        std::cout << "Rozwiazanie = " << bestCost << std::endl << std::endl;
    }
    delete[] array;
}
// Finding best permutation for brute force
void TravellingSalesian::permutation(int T[], int ix){

    if (ix < cityNumbers - 1) {

        for (int i = ix; i < cityNumbers; i++) {

            // swapping two elements
            swap(T[ix], T[i]);
            permutation(T, ix + 1);
            // return elements
            swap(T[ix], T[i]);
        }
    }
    else {

        // after permutation find cost and compare with temporary best cost
        int temporaryCost = costBruteForce(T);

        if (temporaryCost < bestCost) {

            for (int i = 0; i < cityNumbers; i++) {

                bestBruteForce[i] = T[i];
            }
            bestCost = temporaryCost;
        }
    }

}
// swapping two elements
void TravellingSalesian::swap(int &a, int &b) {

    int c = a;
    a = b;
    b = c;
}

//
int TravellingSalesian::costBruteForce(int array[]){
    int cost = 0;

    for (int i = 0; i < cityNumbers - 1; i++) {

        // Getting cost of journey from matrix
        cost += matrix[array[i]][array[i + 1]];
    }

    // Connecting last city with first city
    cost += matrix[array[cityNumbers - 1]][array[0]];

    return cost;
}

void TravellingSalesian::branchAndBound(bool isPrinting){

    // temporary nodes
    node u, v;
    // temporary path
    std::vector<int> temporaryPath;
    //  Final path with solution
    std::vector<int> finalPath;

    // Initialization of node with initial values starting from 0
    temporaryPath.push_back(0);
    v.bound = 0;
    v.level = 0;
    v.path = temporaryPath;
    v.bound = bottomBound(v);

    // Initialization of note with initial values
    u.bound = 0;
    u.level = 0;

    // Creation priority queue
    std::priority_queue < node, std::vector<node>, nodeCompare > myQueue;

    // At the beginning length of route is infinity
    int minLength = INT_MAX;

    // Insertion first vertex to priority queue
    myQueue.push(v);

    // Until queue has vertexes continue
    while (!myQueue.empty()) {

        // Taking from queue vertex to do some operations with it
        v = myQueue.top();
        myQueue.pop();

        // checking if we found better bound
        if (v.bound < minLength) {

            // going to next level of our tree
            u.level = v.level + 1;

            // making possible permutations collection solutions
            for (int i = 1; i < cityNumbers; i++) {

                // if we didnt find this vertex in temporary path our solutions
                if (std::find(v.path.begin(), v.path.end(), i) == v.path.end()) {

                    // adding found 'free' vertex
                    u.path = v.path;
                    u.path.push_back(i);

                    if (u.level == cityNumbers - 2) {
                        for (int j = 1; j < cityNumbers; j++) {
                            if (std::find(u.path.begin(), u.path.end(), j) == u.path.end()) {

                                // adding to the path last unvisited city
                                u.path.push_back(j);
                                break;
                            }
                        }

                        // adding to the end of patch 0 to return to the beginning
                        // (not necessary but it helps to fing length of path
                        u.path.push_back(0);

                        if (length(u) < minLength) {
                            minLength = length(u);
                            finalPath = u.path;
                        }
                    }
                    else {

                        // set bound in case we dont end checking path
                        u.bound = bottomBound(u);

                        // if solution is "possible" add to queue
                        if (u.bound < minLength) {
                            myQueue.push(u);
                        }
                    }
                }
            }
        }
    }

    if (isPrinting) {
        std::cout << std::endl << "Metoda podzialu i ograniczen" << std::endl;
        std::cout << "Sciezka = ";


        // display our solution
        for (int i = 0; i < finalPath.size(); i++) {

            if (i != 0) std::cout << " - ";
            std::cout << finalPath[i];
        }

        // display size of our solution
        u.path = finalPath;
        std::cout << std::endl << "Rozwiazanie = " << length(u) << std::endl << std::endl;
    }

}

// counting bottom bound
int TravellingSalesian::bottomBound(node a) {

    // bottom bound consists of current length
    int bound = length(a);

    for (int i = 0; i < cityNumbers; i++) {

        // counting min values for non visited vertexes, blocking unnecessary rows of matrix
        if (check(a, i)) {
            continue;
        }

        int minimum = INT_MAX;
        for (int j = 0; j < cityNumbers; j++) {

            // blocking unnecessary columns of matrix
            if (check2(a, j)) {
                continue;
            }

            // blocking going to yourself
            if (i == j) {
                continue;
            }

            // blocking closing cycle too early
            if (a.path[a.path.size() - 1] == i && j == 0) {
                continue;
            }

            // counting minimum from filtered row
            if (matrix[i][j] < minimum && matrix[i][j] > 0) {
                minimum = matrix[i][j];
            }
        }

        if (minimum != INT_MAX) {
            bound += minimum;
        }
    }

    return bound;
}
// counting length of route from root to node given as function argument
int TravellingSalesian::length(node a) {

    int length = 0;

    // counting length of all saved route
    for (int i = 0; i < a.path.size() - 1; i++) {
        length += matrix[a.path[i]][a.path[i + 1]];
    }

    return length;
}

// checking if vertex i is in path a, searching in first n-1 vertexes from path
bool TravellingSalesian::check(node a, int i) {
    for (int z = 0; z < a.path.size() - 1; z++) {
        if (i == a.path[z]) {
            return true;
        }
    }
    return false;
}

// checking if vertex i is in path a, searching in last n-1 vertexes from path
bool TravellingSalesian::check2(node a, int i) {
    for (int z = 1; z < a.path.size(); z++) {
        if (i == a.path[z]) {
            return true;
        }
    }
    return false;
}

