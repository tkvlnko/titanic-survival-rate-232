#include <vector>

typedef std::vector<std::vector<std::string>> stringMatrix;
enum CSV_FIELDS {PassengerId, Survived, Pclass, Name, 
                Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked };

stringMatrix readCsv(const std::string& filePath);
void printMatrix(stringMatrix matrix);

double defineRate(short age, short pclass, short sex);
void fillNan (stringMatrix& matrix, int columnNum);
void fillRate (stringMatrix& matrix);
void writeCsv(const std::string& filePath, const stringMatrix& matrix);

