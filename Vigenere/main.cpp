/********************************************************************
* AUTOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSIDAD: Universidad de La Laguna
* ASIGNATURA: Seguridad en sistemas informaticos
* VERSION: 2.0
* PRACTICA: 01
* TITUTLO: El cifrado de vigenere
* DESCRIPTION: un cifrado basado en diferentes series de caracteres
* o letras del cifrado César formando estos caracteres una tabla.
* REFERENCIA: https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re
* COMPILACION: make
*              make clean (para eliminar)
* *****************************************************************/

#include <iostream>
#include "cv.hpp"
#include <vector>


int main(){

    std::string result;
    int opcion;
    int num = 0;
    while(num == 0){
        std::cout << "Que operacion quieres realizar con el metodo 'cifrado de Vigenere':" << std::endl
                << "1. Cifrado." << std::endl
                << "2. Descifrado." << std::endl
                << "3. Salir al programa" << std::endl;
        std::cout << "Tu opcion es:";      
        std::cin >> opcion;
        if(opcion == 1) {
            std::string passwd_C;
            std::cout << "Dime la clave que quiere cifrar:";
            std::cin >> passwd_C;

            std::string msg_orignal;
            std::cout << "Que mensaje quieres cifrar:";
            std::cin >> msg_orignal;    
            Vigenere_Cipher a;
            a.Vigenere_encrypt(passwd_C, msg_orignal, result);

        }else if(opcion == 2) {
            std::string msg_Desc;
            std::string passwd_Desc;
            std::string msg_original;
            std::cout << "Dime la clave que quiere descifrar:";
            std::cin >> passwd_Desc;
            std::cout << "Que mensaje quieres descifrar:";
            std::cin >> msg_Desc;
            Vigenere_Cipher a;
            a.Vigenere_decrypt(passwd_Desc, msg_Desc, msg_original);
        }else {
            num ++;
        }
    }
}