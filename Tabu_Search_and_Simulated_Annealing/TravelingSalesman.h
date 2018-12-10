//
// Created by Kuba on 02.12.2018.
//

#ifndef PEA2PROJECT_TRAVELINGSALESMAN_H
#define PEA2PROJECT_TRAVELINGSALESMAN_H

#include <vector>
#include <fstream>
#include <string>

class TravelingSalesman {
private:

    std::vector< std::vector<int>* >* matrix;

    void readMatrixRow(int size, std::ifstream& file, int row);
    int getSizeMatrix(std::ifstream& file);
    void readCosts(std::ifstream& file);
    int stringToInt(const std::string &string);

public:

    TravelingSalesman();
    ~TravelingSalesman();

    bool fileToMatrix(std::string filePath);
    std::string getMatrixToString();
    int getSize();
    void setSize(int count);
    int getCost(int row, int column);
    void setCost(int cost, int beginning, int destination);



};


#endif //PEA2PROJECT_TRAVELINGSALESMAN_H
