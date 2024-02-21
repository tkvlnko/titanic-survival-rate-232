#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <cstdint>
#include <iterator>
#include <numeric>

// #include "ortools/algorithms/knapsack_solver.h"

typedef std::vector<std::vector<std::string>> stringMatrix;
typedef std::map<std::string, std::map<size_t, double>> obesityGenderMap;

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
                Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked, Value};

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

struct Passenger{
    size_t id;
    std::string name;
    std::string sex;
    size_t pclass;
    double value;
    size_t age;
};

bool comp(std::vector<std::string> left, std::vector<std::string> right){
    return left[CSV_FIELDS::Value] > right[CSV_FIELDS::Value];
}


std::ostream& operator<< (std::ostream& stream, const Passenger& pass){ //без & не выведет
    stream << pass.id << '\t' << pass.name << '\t' << pass.value << '\n';
    return stream;
}


void selectSurvivors(stringMatrix matrix, size_t boats, size_t seats)
{
    std::sort(matrix.begin(), matrix.end(), comp); //comp = "lambda function"
    std::vector<std::vector<Passenger>> survived;
    for (size_t j = 1; j<= boats; j++)
    {
        std::vector<Passenger> boat;
        for (size_t i = 1; i <= seats; i++){
        Passenger pass {std::stoul(matrix[i][CSV_FIELDS::PassengerId]), matrix[i][CSV_FIELDS::Name], matrix[i][CSV_FIELDS::Sex], 
                    std::stoul(matrix[i][CSV_FIELDS::Pclass]), std::stod(matrix[i][CSV_FIELDS::Value]), std::stoul(matrix[i][CSV_FIELDS::Age])};
        // pass.id = matrix[i][CSV_FIELDS::PassengerId];
        boat.push_back(pass);
        }
        survived.push_back(boat);
    }
    size_t count = 1;
    for (const std::vector<Passenger>& boat: survived)
    {
        std::cout << "boat " << count++ << '\n';
        for (const Passenger& elem: boat)
            std::cout << elem; //вызывает operator<< для типа данных passenger
        std::cout << "------------\n";
    }    
}

struct personObesity{
    std::string gender;
    size_t age;
    double weight;
};


obesityGenderMap getObesity(const std::string& filePath) {
    obesityGenderMap map{{"Male",{}}, {"Female",{}}};
    obesityGenderMap counter{{"Male",{}}, {"Female",{}}};
    std::ifstream inputfile(filePath);
    if(!inputfile) {
        std::cout << "cringe";
        return map;
    }

    std::string line;
    while(std::getline(inputfile, line)) {
        std::stringstream ss (line);
        std::string field;
        std::vector <std::string> tokens;
        size_t counterField = 0;
        personObesity po;
        while (std::getline(ss, field, ',') && counterField++ < 4) { // откуда + куда засунуть + по какому знаку делить
            switch (counterField){
                case 0:
                    po.gender = field;
                    break;
                case 1:
                    po.age = std::stoul(field);
                    break;
                case 3:
                    po.weight = std::stod(field); 
                    break;
                default:
                    break;
            }
        }
        // matrix.push_back(tokens); TO BE CONTINUED‼️!!!!!‼️‼️🚼
    }
    return map;
}







void generateWeights(stringMatrix& matrix){
    
}


