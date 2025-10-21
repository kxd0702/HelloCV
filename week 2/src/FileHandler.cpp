#include "FileHandler.h"
#include <fstream>
#include <stdexcept>
using namespace std;
string FileHandler::readFromFile(const string& filePath){
    ifstream file(filePath);
    if(!file.is_open()){
        throw runtime_error("无法打开文件：" + filePath);
        
    }
    string
content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
   file.close();
   return content;
   
}
bool FileHandler::writeToFile(const string& text, const string& filePath){
    ofstream file(filePath);
    if(!file.is_open()){
        return false;
    }
    file << text;
    file.close();
    return true;
}
