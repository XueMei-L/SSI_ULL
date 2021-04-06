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

#include <iostream>
#include <vector>
#include <cassert>              //assert
#include "snow3gyaes.hpp"

//Function main
int main() {
    std::string algoritmo;
    std::string byte1;
    std::string byte2;
    SNOW3GYAES* ptr_snow3gyaes = new SNOW3GYAES();
    std::cout << "-------------------------Bienvenido al algoritmo de snow 3G y AES-------------------------" << std::endl;
    int i = 0;
    int choose = 0;
    while (i == 0) {
        std::cout << "Introduzca el algoritmo que quieres realizar, o salir del programa introduciendo 'EXIT':" << std::endl;
        std::cout << "1. SNOW_3G" << std::endl
                  << "2. AES" << std::endl << std::endl
                  << "Su opcion es:";
        std::cin >> algoritmo;
        if(algoritmo == "SNOW_3G" || algoritmo == "snow_3g") {
            choose = 1;
        }else if(algoritmo == "AES" || algoritmo == "aes") {
            choose = 2;
        }else if(algoritmo == "EXIT" || algoritmo == "exit"){
            choose = 3;
        }
        switch (choose) {
        case 1:
            ptr_snow3gyaes->snow3gOrAes(algoritmo);
            i = 1;
            break;
        case 2:
            ptr_snow3gyaes->snow3gOrAes(algoritmo);
            i = 1;
            break;
        case 3:
            i = 2;
            break;
        default:
            std::cout << std::endl << "No existe dicho algoritmo o operacion, vuelva a intentar." << std::endl;
            break;
        }
    }
    if(i == 1) {
    for(int i = 0; i < 2; i++) {
        std::cout << "Introduzca" << " byte" << i + 1 << " en hexadecimal:";
        std::cin >> byte1;   
        ptr_snow3gyaes->hexToBin(byte1, i); 
    }
    ptr_snow3gyaes->algorithm();
    ptr_snow3gyaes->printResult();
    }
    delete ptr_snow3gyaes;
}
