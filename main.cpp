/********************************************************************
* AUTOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSIDAD: Universidad de La Laguna
* ASIGNATURA: Seguridad en sistemas informaticos
* VERSION: 1.0
* PRACTICA: 08
* TITUTLO: Diffie_Hellman_Elgamal
* DESCRIPTION: Cifrado utilizando Diffie_Hellman y Elgamal
* COMPILACION: make
*              make clean (para eliminar)
* *****************************************************************/

#include <iostream>
#include <cmath>
#include "diffie_hellman_elgamal.hpp"

/**
 * @description: funcion main para preguntar a los usuarios que operacion desea realizar
*/
int main() {
    std::cout << "-----Bienvenido al programa del del algoritmo de claves de Diffie-Hellman y el cifrado ElGamal-----" << std::endl;
    
    int i = 0;
    int choose;
    while(i == 0) {
        std::cout << "Introduzca la operacion que quiere:\n"
                  << "1. Realizar el algoritmo de Diffie-Hellman y el cifrado ElGamal\n"
                  << "2. Salir del programa" << std::endl;
        std::cout << "Tu opcion es:";
        std::cin  >> choose;
        switch (choose) {
            case 1:
            {
                DH_GM* ptr_obj = new DH_GM();
                ptr_obj->algoritmo();
                delete ptr_obj;
                int veces = 0;
                while(veces == 0) {
                    std::string op;
                    std::cout << "Desea realizar otra vez el algoritmo? (y/n)";
                    std::cin >> op;
                    if(op == "y" || op == "yes") {
                    DH_GM* ptr_obj = new DH_GM();
                    ptr_obj->algoritmo();
                    delete ptr_obj;
                    }else if (op == "n" || op == "no") {
                        veces++;
                    }else {
                        std::cout << "No has introducido una opcion correcta." << std::endl;
                    }
                }
                break;
            }
            case 2:
            {
                i = 1;
                break;
            }
            
            default:
                std::cout << "\nNo es un opcion correcta, vuelva a introducir una opcion valida." << std::endl << std::endl;
                break;
        }
    }
    
}