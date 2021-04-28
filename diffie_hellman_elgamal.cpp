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

#include "diffie_hellman_elgamal.hpp"

DH_GM::DH_GM(){}

DH_GM::~DH_GM(){};

/**
 * @description: realizar el proceso de calculo de valores publicos y clave secreta
 * ademas, tambien realiza el proceso de cifrar y descifrar.
*/
void DH_GM::algoritmo()
{
    int p; int a; int k; int x; int m;

    std::cout << "\n\nintroduzca las varias necesarias:\n"
              << "p (p tiene que ser un numero primo) = ";
    std::cin >> p;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "k = ";
    std::cin >> k;
    std::cout << "x = ";
    std::cin>> x;
    std::cout << "m = ";
    std::cin >> m;

    //Enviar el valor publico desde A->B  YA = a^k(mod p)
    int YA = myPow(a, k, p);

    //Enviar el valor publico desde B->A  YB = a^x(mod p)
    int YB = myPow(a, x, p);

    //Enviar la clave secreata compartida A->B
    int xk = x * k;
    int K = myPow(a, xk, p);
    
    //Mensaje cifrado
    int C = (K * m) % p;

    //Inverso de K
    int KInv = extendedEuclid(K, p);

    //Mensaje descifrado
    int M = (KInv * (K * m)) % p;

    //Mostrar resultados
    std::cout << "p = " << show(p) << "   "
              << "a = " << show(a) << "   "
              << "k = " << show(k) << "   "
              << "x = " << show(x) << "   "
              << "m = " << show(m) << "   \n"
              << "YA = " << show(YA) << "  "
              << "YB = " << show(YB) << "  "
              << "K = " << show(K) << "   "
              << "C = " << show(C) << "   "
              << "K^(-1) = " << show(KInv) << "   "
              << "M = " << show(M) << std::endl;
}

/**
 * @param a: base
 * @param b: potencia
 * @param m: divisor
 * @descrption: realizar la potencia y la division para obtener el resto
 * @return: el resto
*/
inline int DH_GM::myPow(int a, int b, int m) {
        int res = 1;
        a %= m;
        while (b != 0) {
            if ((b & 1) == 1)
                 res = (res * a) % m;
             a = (a * a) % m;
             b >>= 1;
        }
        return res;
}

/**
 * @param a: igual que k
 * @param b: igual que p
 * @description: realizar la inversa de K^-1
 * @return: K^-1
*/
inline int DH_GM::extendedEuclid(int a, int b) {
        int x = 1, y = 0;
        int xLast = 0, yLast = 1;
        int q, r, m, n;
        while (a != 0) {
            q = b / a;
            r = b % a;
            m = xLast - q * x;
            n = yLast - q * y;
            xLast = x, yLast = y;
            x = m, y = n;
            b = a, a = r;
        }
        int absoluto = abs(xLast);
        return absoluto;
}

/**
 * @param value: numero que desea imprimer
 * @return: numero que quiere imprimer por la pantalla
*/
int DH_GM::show(int value) {
    return value;
}
