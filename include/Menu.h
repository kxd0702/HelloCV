#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;
class Crypto;
class FileHandler;
class Menu{
private:
     Crypto* crypto;
     FileHandler* fileHandler;
public:
     Menu(Crypto* c, FileHandler* f);
     void showMenu();
     void handleTextEncrypt();
     void handleTextDecrypt();
     void handleFileEncrypt();
     void handleFileDecrypt();
};
#endif
