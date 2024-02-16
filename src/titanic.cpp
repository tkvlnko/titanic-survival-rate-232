#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

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

double WEIGHTS[] {0.5, 0.25, 0.25};
double defineRate(short age, short pclass, short sex) {
    return (1.0/(age + 1)) * WEIGHTS[0] + (1.0/pclass) *  WEIGHTS[1] + ((1 + sex)/2.0) * WEIGHTS[2];
}


void fillNan (stringMatrix& matrix, int columnNum) {
    std::vector<std::string> column; 
    for(size_t i = 0; i < matrix.size(); i++) {
        if(!matrix[i][columnNum].empty()) {
            column.push_back(matrix[i][columnNum]);
        }
    }
    std::sort(column.begin(), column.end());
    std::string median = column[column.size() / 2];

    for(size_t i = 0; i < matrix.size(); i++) {
        if(matrix[i][columnNum].empty()) {
            matrix[i][columnNum] = median;
        }
    }
}

enum CSV_FIELDS {PassengerId, Survived, Pclass, Name, 
                Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked };

void fillRate (stringMatrix& matrix) {
    matrix[0].push_back("Rate");
    for(size_t i = 1; i < matrix.size(); i++) {
        try {
            double rate = defineRate(std::stoi(matrix[i][CSV_FIELDS::Age]), 
                                            std::stoi(matrix[i][CSV_FIELDS::Pclass]), 
                                            matrix[i][CSV_FIELDS::Sex] == "male" ? 0 : 1);
                    matrix[i].push_back(std::to_string(rate));
        } catch(...) {
            // std::cout << matrix[i][CSV_FIELDS::Sex] << '\t' <<
            // matrix[i][CSV_FIELDS::Age] << '\t' <<
            // matrix[i][CSV_FIELDS::Pclass] << '\n' ;
        }
        
    }
}

void writeCsv(const std::string& filePath, const stringMatrix& matrix) {
        std::ofstream outputfile(filePath);
        for (const std::vector<std::string>& row: matrix) { // давайте не делать копию пж
            for (const std::string& field: row) {
                outputfile << field << ';' ;
            }
            outputfile << '\n' ;
        }
}

