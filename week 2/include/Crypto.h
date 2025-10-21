#ifndef CRYPTO_H
#define CRYPTO_H
#include <string>
using namespace std;
class Crypto{
public:
    string caesarEncrypt(const string& text, int key);
    string caesarDecrypt(const string& cipherText, int key);
};
#endif 
