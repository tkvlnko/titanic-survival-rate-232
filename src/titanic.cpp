#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

typedef std::vector<std::vector<std::string>> stringMatrix;

stringMatrix readCsv(const std::string& filePath) {
    stringMatrix matrix;
    std::ifstream inputfile(filePath);
    if(!inputfile) {
        std::cout << "cringe";
        return matrix;
    }

    std::string line;
    while(std::getline(inputfile, line)) {
        std::stringstream ss (line);
        std::string field;
        std::vector <std::string> tokens;
        while (std::getline(ss, field, ';') ) { // откуда + куда засунуть + по какому знаку делить
            tokens.push_back(field);
        }
        matrix.push_back(tokens);
    }
    return matrix;
}

void printMatrix(stringMatrix matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << '\n';
    }
}