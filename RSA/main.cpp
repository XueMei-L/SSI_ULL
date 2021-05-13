/********************************************************************
* AUTOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSIDAD: Universidad de La Laguna
* ASIGNATURA: Seguridad en sistemas informaticos
* VERSION: 4.0
* PRACTICA: 09
* TITUTLO: RSA
* DESCRIPTION: El cifrado de clave publica RSA
* REFERENCIA: https://es.wikipedia.org/wiki/RSA
* COMPILACION: make
*              make clean (para eliminar)
* *****************************************************************/

#include <iostream>
#include "rsa.hpp"

int main(int argc, char *argv[]) {
    
    RSA* ptr_obj = new RSA();
    ptr_obj->algorithm();

    return 0;
}