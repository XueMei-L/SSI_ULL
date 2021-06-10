#ifndef CV_HPP
#define CV_HPP

#include <iostream>

class Vigenere_Cipher{

    public:
        Vigenere_Cipher();
        ~Vigenere_Cipher();
        void algoritmo();
        void Vigenere_encrypt(std::string, std::string, std::string);
        void Vigenere_decrypt(std::string, std::string, std::string);

    private:

};

#endif