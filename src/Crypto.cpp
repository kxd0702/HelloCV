#include "Crypto.h"
#include <cctype>
using namespace std;
string Crypto::caesarEncrypt(const string& text, int key){
   string result;
   for(char c : text){
       if(isalpha(c)){
           char base = isupper(c) ? 'A' : 'a';
           result +=(c-base+key)%26+base;
       }else{
       result += c;
       
         }
       }
       return result;
}
string Crypto::caesarDecrypt(const string&cipherText, int key){
    return caesarEncrypt(cipherText, -key);
}
