#include <iostream>
#include "06_aes.hpp"


void aes::algoritmo() {
    std::cout << "\n--------------------Bienvenido al algoritmo AES-------------------------\n";
    std::cout << "\n>> Que operacion quiere realizar con el algoritmo 'AES'"
              << "\n>> 1. Cifrar con AES"
              << "\n>> 2. Volver al menu incial."
              << "\nSu option es: ";
    std::string option;
    std::cin >> option;
    int k = 0;
    while(k == 0) {
        if(option == "1") {
            algoritmo1();
            k = 1;
        }else if(option == "2") {
            std::cout << "\n--------------------Saliendo al algoritmo AES-----------------\n\n";
            k = 1;
        }else{
            std::cout << "\n>> No es una opcion, por favor, vuelva a introducir una option:";
            std::cin >> option;
        }
    }
}