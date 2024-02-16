#include <vector>

typedef std::vector<std::vector<std::string>> stringMatrix;

stringMatrix readCsv(const std::string& filePath);
void printMatrix(stringMatrix matrix);