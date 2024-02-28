#include "titanic.h"
// #include "ortools/algorithms/knapsack_solver.h"

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

personObesity personObesity::operator+(const personObesity& x) const {
    personObesity newTEMP1 {gender, age, weight+x.weight};
    return newTEMP1;
}

obesityGenderMap getObesity(const std::string& filePath) {
    obesityGenderMap map{{"Male",{}}, {"Female",{}}};
    obesityGenderMap counter{{"Male",{}}, {"Female",{}}};
    std::ifstream inputfile(filePath);
    if(!inputfile) {
        std::cout << "cringe";
        return map;
    }

    std::string line;
    std::vector<personObesity> vectorWomen;
    std::vector<personObesity> vectorMen;
    while(std::getline(inputfile, line)) {
        std::stringstream ss (line);
        std::string field;
        std::vector <std::string> tokens;
        size_t counterField = 0;
        personObesity po;
        while (std::getline(ss, field, ',') && counterField++ < 4) { // откуда + куда засунуть + по какому знаку делить
            try {
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
        catch (...){}
        }
        // matrix.push_back(tokens); TO BE CONTINUED‼️!!!!!‼️‼️🚼
        if (po.gender == "Female")
            vectorWomen.push_back(po);
        else
            vectorMen.push_back(po);
    }
    std::map<size_t, double> tempMap;
    for (size_t i = 0; i < 100; i++) {
        std::vector<personObesity> temp;
        std::copy_if (vectorWomen.begin(), vectorWomen.end(), std::back_inserter (temp), [i](const personObesity& x){return x.age == i;});
        if (temp.size() == 0)
            tempMap.insert({i, 0});
        else
            std::reduce(temp.begin(), temp.end());
        temp.clear();

    }
    //std::copy_if

    return map;
}







void generateWeights(stringMatrix& matrix){
    
}


