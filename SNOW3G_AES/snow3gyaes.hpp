/********************************************************************
* AUTOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSIDAD: Universidad de La Laguna
* ASIGNATURA: Seguridad en sistemas informaticos
* VERSION: 3.0
* PRACTICA: 05
* TITUTLO: El cifrado de vigenere
* DESCRIPTION: SNOW 3G O AES se operan entre dos bytes dados
* COMPILACION: make
*              make clean (para eliminar)
* *****************************************************************/

#ifndef SNOW_3G_Y_AES
#define SNOW_3G_Y_AES

#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <bitset>
#include <string>

class SNOW3GYAES{

    public:
        SNOW3GYAES();
        ~SNOW3GYAES();
        void hexToBin(std::string, int);
        void algorithm();
        void snow3gOrAes(std::string);
        void printResult();
    private:
        std::vector<int> byte1;
        std::vector<int> byte2;
        std::vector<int> vecXor;
        std::vector<int> multiple;
        void showVector(std::vector<int>&);
};


#endif