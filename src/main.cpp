#include "Crypto.h"
#include "FileHandler.h"
#include "Menu.h"
using namespace std;
int main() {
    Crypto crypto;
    FileHandler fileHandler;
    Menu menu(&crypto, &fileHandler);
    menu.showMenu();
    return 0; 
}
