//
// Created by Kuba on 02.12.2018.
//

#include "TravelingSalesman.h"
#include <algorithm>

// constructor
TravelingSalesman::TravelingSalesman() {

    matrix = new std::vector< std::vector<int>* >;

}

// destructor
TravelingSalesman::~TravelingSalesman() {

    matrix->clear();
    delete matrix;

}

// converting string to int
int TravelingSalesman::stringToInt(const std::string &string) {

    return atoi(string.c_str());
}

// getting size of matrix
int TravelingSalesman::getSizeMatrix(std::ifstream& file) {
    int position = -1;
    int size = -1;
    std::string line;

    // do while found EDGE_WEIGHT_SECTION in file
    do
    {
        std::getline(file, line);
        position = line.find("DIMENSION: ");
        if (position != std::string::npos)
        {
            //"DIMENSION: " has 11 characters
            position += 11;
            size = stringToInt(line.substr(position));

        }
    } while (line.find("EDGE_WEIGHT_SECTION") == std::string::npos);

    return size;

}

// reading costs in row
void TravelingSalesman::readMatrixRow(int size, std::ifstream& file, int row) {
    std::string cost;

    for (int i = 0; i < size; ++i)
    {
        file >> cost;
        matrix->at(row)->push_back(stringToInt(cost));
    }
}

// reading costs in file
void TravelingSalesman::readCosts(std::ifstream& file) {

    int size = getSizeMatrix(file);
    matrix->clear();

    for (int i = 0; i < size; ++i)
    {
        matrix->push_back(new std::vector<int>);
        readMatrixRow(size, file, i);
    }
}

// reading file to matrix
bool TravelingSalesman::fileToMatrix(std::string filePath) {

    std::ifstream file(filePath);

    if (file.good())
    {
        readCosts(file);
        file.close();

        if (matrix->size() > 0) {
            return true;
        }
    }

    return false;

}

// getting matrix to string
std::string TravelingSalesman::getMatrixToString() {
    std::string stringMatrix = "";

    for (std::size_t i = 0; i < matrix->size(); i++)
    {
        for (std::size_t j = 0; j < matrix->at(i)->size(); j++)
        {

            stringMatrix.append(std::to_string(getCost(i, j)));
            stringMatrix.append(" ");

        }
        stringMatrix.append("\n\n");
    }

    return stringMatrix;

}

// getting matrix size
int TravelingSalesman::getSize() {

    return matrix->size();

}

// setting matrix size
void TravelingSalesman::setSize(int size) {

    matrix->clear();
    for (int i = 0; i < size; ++i)
    {
        matrix->push_back(new std::vector<int>);
        for (int j = 0; j < size; ++j)
        {
            matrix->at(i)->push_back(9999);
        }
    }
}

// getting edge cost
int TravelingSalesman::getCost(int row, int column) {

    return matrix->at(row)->at(column);

}

// setting edge cost
void TravelingSalesman::setCost(int cost, int beginning, int destination) {

    matrix->at(beginning)->operator[](destination) = cost;

}