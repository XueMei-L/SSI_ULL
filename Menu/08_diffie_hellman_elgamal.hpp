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

#ifndef DIFFIE_HELLMAN_ELGAMAL
#define DIFFIE_HELLMAN_ELGAMAL

class DH_GM 
{
    
private:
    int K_inv(int, int);
    int show(int);
    inline int extendedEuclid(int, int);
    inline int myPow(int, int, int);

public:
    DH_GM();
    ~DH_GM();
    void algoritmo1();
    void algoritmo();

};

#endif //DIFFIE_HELLMAN_ELGAMAL