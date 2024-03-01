#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <random>

typedef std::vector<std::vector<std::string>> stringMatrix;
typedef std::unordered_map<std::string, std::map<size_t, double>> obesityGenderMap;
enum CSV_FIELDS {PassengerId, Survived, Pclass, Name, 
                Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked, Value, Weight};


struct Passenger{
    size_t id;
    std::string name;
    std::string sex;
    size_t pclass;
    double value;
    size_t age;
};


struct personObesity{
    std::string gender;
    size_t age;
    double weight;
    personObesity operator+(const personObesity& x) const;
};


stringMatrix readCsv(const std::string& filePath);
void printMatrix(stringMatrix matrix);


double defineRate(short age, short pclass, short sex);
void fillNan (stringMatrix& matrix, int columnNum);
void fillRate (stringMatrix& matrix);
void writeCsv(const std::string& filePath, const stringMatrix& matrix);
void selectSurvivors(stringMatrix matrix, size_t boats, size_t seats);
obesityGenderMap getObesity(const std::string& filePath);
void fillWeights(stringMatrix& matrix, const obesityGenderMap& map);
