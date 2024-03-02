#include "ortools.h"

const std::string PATH = "../data/titanic.csv";

int main() {
    stringMatrix matrix = readCsv(PATH);
    for (int i: {CSV_FIELDS::Age, CSV_FIELDS::Sex, CSV_FIELDS::Pclass})
        fillNan(matrix, i);

    fillRate(matrix);
    // printMatrix(matrix);
    writeCsv("output.csv", matrix);
    // std::cout << defineRate(0, 1, 1);
    selectSurvivors(matrix, 10, 10);
    obesityGenderMap map = getObesity("../data/obesity.csv");
    std:: cout << "DONE getObesity\n";
    fillWeights(matrix, map);
    // printMatrix(matrix);

    operations_research::RunKnapsackExample(matrix);
    return 0;
}

