#include "Menu.h"
#include "Crypto.h"
#include "FileHandler.h"
#include <iostream>
using namespace std;

Menu::Menu(Crypto* c, FileHandler* f) : crypto(c), fileHandler(f) {}

void Menu::showMenu() {
    int choice; 
    do {
        cout << "\n===== 凯撒密码加密解密工具菜单 =====\n";
        cout << "1. 文本加密（凯撒）\n";
        cout << "2. 文本解密（凯撒）\n";
        cout << "3. 文件加密（凯撒）\n";
        cout << "4. 文件解密（凯撒）\n";
        cout << "0. 退出\n";
        cout << "请选择功能: ";
        cin >> choice;       
        switch (choice) {
            case 1: handleTextEncrypt(); break; 
            case 2: handleTextDecrypt(); break; 
            case 3: handleFileEncrypt(); break; 
            case 4: handleFileDecrypt(); break; 
            case 0: cout << "感谢使用，再见！\n"; break; 
            default: cout << "无效选择，请重新输入！\n"; 
        }
    } while (choice != 0); 
}
void Menu::handleTextEncrypt() {
    string text, result; 
    int key; 

    cout << "请输入要加密的文本: ";
    cin.ignore(); 
    getline(cin, text); 

    cout << "请输入凯撒密钥（整数，如3）: ";
    cin >> key;
    result = crypto->caesarEncrypt(text, key);
    cout << "凯撒加密结果: " << result << endl;
}

void Menu::handleTextDecrypt() {
    string cipherText, result; 
    int key; 

    cout << "请输入要解密的文本: ";
    cin.ignore(); 
    getline(cin, cipherText); 

    cout << "请输入凯撒密钥（需与加密时相同）: ";
    cin >> key; 
    result = crypto->caesarDecrypt(cipherText, key);
    cout << "凯撒解密结果: " << result << endl; 
}

void Menu::handleFileEncrypt() {
    string filePath, outPath; 
    int key; 

    cout << "请输入要加密的文件路径（如./input.txt）: ";
    cin.ignore();
    getline(cin, filePath); 

    cout << "请输入凯撒密钥（整数）: ";
    cin >> key; 

    cout << "请输入加密后保存的文件路径（如./encrypted.txt）: ";
    cin.ignore(); 
    getline(cin, outPath); 

    try {
        string content = fileHandler->readFromFile(filePath);
        string encrypted = crypto->caesarEncrypt(content, key);
        if (fileHandler->writeToFile(encrypted, outPath)) {
            cout << "文件加密成功！结果已保存到: " << outPath << endl;
        } else {
            cout << "文件保存失败！\n";
        }
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}

void Menu::handleFileDecrypt() {
    string filePath, outPath; 
    int key;

    cout << "请输入要解密的文件路径（如./encrypted.txt）: ";
    cin.ignore(); 
    getline(cin, filePath); 

    cout << "请输入凯撒密钥（需与加密时相同）: ";
    cin >> key; 

    cout << "请输入解密后保存的文件路径（如./decrypted.txt）: ";
    cin.ignore(); 
    getline(cin, outPath); 
    try {
        string content = fileHandler->readFromFile(filePath);
        string decrypted = crypto->caesarDecrypt(content, key);
        if (fileHandler->writeToFile(decrypted, outPath)) {
            cout << "文件解密成功！结果已保存到: " << outPath << endl;
        } else {
            cout << "文件保存失败！\n";
        }
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}
