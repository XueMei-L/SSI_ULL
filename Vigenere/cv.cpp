#include <iostream>
#include "cv.hpp"

Vigenere_Cipher::Vigenere_Cipher(){}
Vigenere_Cipher::~Vigenere_Cipher(){}

void Vigenere_Cipher::Vigenere_encrypt(std::string pw, std::string msg, std::string result) {
    
    result.resize(msg.size());
    std::string new_vector;                                     
    for(int i = 0; i < pw.size(); i++) {
        if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i]);
        }else if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i] - 32);
        }else {
            new_vector.push_back(pw[i]);
        }
    }

    int count = 0;
    for(int i = 0; i < msg.size(); i++) {
        if((int)(msg[i] > 64 && (int)(msg[i]) < 91)) {
            result[i] = (char)((((int)msg[i] - 65 + (new_vector[(count++)%new_vector.size()]-'A')) % 26) + 65);
        }else if((int)msg[i] > 96 && (int)msg[i] < 123) {
            result[i] = (char)((((int)msg[i] - 97 + (new_vector[(count++) % new_vector.size()] - 'A')) % 26) + 65);
        }else {
            result[i] = msg[i];
        }
    }

    std::cout << "CLAVE:   " << pw << std::endl;
    std::cout << "MGS:     ";
    for(int i = 0; i < msg.size(); i++) {
        if((i != 0) && (i % pw.size() == 0)){
            std::cout << " ";
        }
        std::cout << msg[i];
    }
    std::cout << std::endl;

    std::cout << "CIFRADO: ";
    for(int i = 0; i < result.size(); i++) {
        if((i != 0) && i % pw.size() == 0){
            std::cout << " ";
        }
        std::cout << result[i];
    }
    std::cout << std::endl;

}

void Vigenere_Cipher::Vigenere_decrypt(std::string pw, std::string result, std::string msg) {

    msg.resize(result.size());
    std::string new_vector;   
    for(int i = 0; i < pw.size(); i++) {
        if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i]);
        }else if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i] - 32);
        }else {
            new_vector.push_back(pw[i]);
        }
    }

    int count = 0;
    for (int i = 0; i < result.size();i++) {
        if ((int)result[i]>64 && (int)result[i] < 91) {
        msg[i] = (char)((((int)result[i] - 65 + 52 - (new_vector[(count++) % new_vector.size()] - 'A')) % 26) + 65);//减去65-k取模可得到前移k位的ascii（大写） //加26使其非负
        }
        else if ((int)result[i] > 96 && (int)result[i] < 123) {
        msg[i] = (char)((((int)result[i] - 97 + 52 - (new_vector[(count++) % new_vector.size()] - 'A') ) % 26) + 65);//减去97-k取模可得到前移k位的ascii（小写）//加26使其非负
        }
        else {
        msg[i] = result[i];
        }
    }
        std::cout << "CLAVE:        " << pw << std::endl
                  << "Msg_cifrado:  " << result << std::endl
                  << "Msg_original: " << msg << std::endl << std::endl;
}