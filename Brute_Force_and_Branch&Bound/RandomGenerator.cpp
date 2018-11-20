//
// Created by Kuba on 06.11.2018.
//

#include "RandomGenerator.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>




RandomGenerator::RandomGenerator(){

}

RandomGenerator::~RandomGenerator() {

}

void RandomGenerator::getTravellingSalesman(int cityNumbers) {

    srand(time(NULL));
    std::fstream file;
    file.open("dane",std::ios::out);

    if(!file.good()){
        std::cout << "Blad tworzenia pliku"<<std::endl;
        return;
    }

    else {
        file << cityNumbers<<std::endl;
        // Allocation memory for adjacency matrix
        int **matrix = new int *[cityNumbers];

        for (int i = 0; i < cityNumbers; i++) {
            matrix[i] = new int[cityNumbers];
        }

        for (int i = 0; i < cityNumbers; i++) {
            for (int j = i; j < cityNumbers; j++) {
                if (i == j) {
                    matrix[i][j] = -1;
                } else {
                    matrix[i][j] = rand() % 50 + 1;
                    matrix[j][i] = rand() % 50 + 1;
                }
            }
        }
        for(int i = 0; i < cityNumbers; i++)
        {
            for(int j = 0; j < cityNumbers; j++)
            {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
        for(int i = 0; i < cityNumbers; i++)
        {
            delete [] matrix[i];
        }
        delete [] matrix;
    }
    file.close();
    return;
}



