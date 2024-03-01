#include "titanic.h"

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
                    matrix[i].push_back(std::to_string(int(rate * 100)));
        } catch(...) {}
        
    }
}


double randomGenerator(double weight) {
    std::random_device rd; //говорим что будем использовать рандомазер
    std::mt19937 gen(rd()); //правило по которому работает рандомайзер, rd - запускает его
    std::uniform_real_distribution<double> distrib(-weight*0.5, weight); //нормальное распределение - то как должен выглядеть отрезок сгенерированных нами чисел
    return distrib(gen); //выбираем число из отрезка по правилу
}

// заполняем вес каждого человека = среднее + рандомное отклонение (может быть <0)
void fillWeights(stringMatrix& matrix, const obesityGenderMap& map) {
    matrix[0].push_back("Weight");
    for(size_t i = 1; i < matrix.size(); i++) {
        try {
            size_t age = std::stoi(matrix[i][CSV_FIELDS::Age]);
            std::string sex = (matrix[i][CSV_FIELDS::Sex] == "male" ? "Male" : "Female");

            const std::map<size_t, double>& ageMap = map.at(sex);
            double weight = ageMap.lower_bound(age)->second;
            matrix[i].push_back(std::to_string(int (weight + randomGenerator(weight))));
            // std::cout << "age: " << age << '\t' << "weight: " << weight << '\t' << "sex: " << weight << '\n';

        } catch(...) {};
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

    // size_t count = 1;
    // for (const std::vector<Passenger>& boat: survived)
    // {
    //     std::cout << "boat " << count++ << '\n';
    //     for (const Passenger& elem: boat)
    //         std::cout << elem; //вызывает operator<< для типа данных passenger
    //     std::cout << "------------\n";
    // }
}


personObesity personObesity::operator+(const personObesity& x) const {
    personObesity newTEMP1 {gender, age, weight+x.weight};
    return newTEMP1;
}


obesityGenderMap getObesity(const std::string& filePath) {
    obesityGenderMap map;
    std::ifstream inputfile(filePath);
    if(!inputfile) {
        std::cout << "cringe";
        return map;
    }

    std::string line;
    std::vector<personObesity> vectorWomen;
    std::vector<personObesity> vectorMen;

    //здесь мы только считали
    while(std::getline(inputfile, line)) {
        std::stringstream ss (line);
        std::string field;
        std::vector <std::string> tokens;
        size_t counterField = 0;
        personObesity po;
        while (std::getline(ss, field, ',') && counterField < 4) { // откуда + куда засунуть + по какому знаку делить
        
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
        catch (...){
        }
        counterField++;
        }

        if (po.gender == "Female")
            vectorWomen.push_back(po);
        else
            vectorMen.push_back(po);
    }
    
    std::map<size_t, double> tempMapMan;
    std::map<size_t, double> tempMapWomen;
    for (size_t i = 0; i < 100; i++) {
        std::vector<personObesity> tempMan;
        std::vector<personObesity> tempWoman;
        std::copy_if (vectorWomen.begin(), vectorWomen.end(), std::back_inserter (tempWoman), [i](const personObesity& x){return x.age == i;});
        std::copy_if (vectorMen.begin(), vectorMen.end(), std::back_inserter (tempMan), [i](const personObesity& x){return x.age == i;});
        if (tempMan.size() != 0) {
            personObesity sumOfWeights = std::reduce(tempMan.begin(), tempMan.end());
            tempMapMan.insert({i, ((sumOfWeights.weight)/tempMan.size())}); 
            // std::cout <<i << '\t'<< (sumOfWeights.weight  * 0.8)/tempMan.size() << '\t'<< rnd <<'\n';
        }
        if (tempWoman.size() != 0) {
            personObesity sumOfWeights = std::reduce(tempWoman.begin(), tempWoman.end());
            tempMapWomen.insert({i, ((sumOfWeights.weight)/tempWoman.size())});
            std::cout << "age:   " << i << '\t'<< "average weigth:   " << (sumOfWeights.weight  * 0.8)/tempWoman.size() <<'\n';
        }
    }
    map.insert({"Male", tempMapMan});
    map.insert({"Female", tempMapWomen});
    return map;
}
