#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <string>
using namespace std;
class FileHandler{
public:
     string readFromFile(const string& filePath);
     bool writeToFile(const string& text, const string& filePath);
};
#endif
