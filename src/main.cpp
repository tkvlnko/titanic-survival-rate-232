#include <iostream>
#include <vector>
#include <string>
#include "titanic.h"


const std::string PATH = "../data/titanic.csv";

int main() {
    stringMatrix matrix = readCsv(PATH);
    printMatrix(matrix);
    return 0;
}