#include <iostream>
#include "11_ffa.hpp"


ffa::ffa(/* args */){}
ffa::~ffa(){}

void ffa::algoritmo(){
    std::cout << "\n-----------------Bienvenido al algoritmo de Feige-Fiat-Shamir-----------------\n";
    std::cout << "\n>> Que operacion quiere realizar con el algoritmo 'Feige-Fiat-Shamir'"
              << "\n>> 1. Comprobar la identidad de A."
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
            std::cout << "\n-----------------Saliendo al algoritmo de Feige-Fiat-Shamir-----------------\n\n";
            k = 1;
        }else{
            std::cout << "\n>> No es una opcion, por favor, vuelva a introducir una option:";
            std::cin >> option;
        }
    }
}
//Inicializacion
void ffa::algoritmo1() {

    //Los valores de p y q
    int p, q;
    std::cout << ">> Introduzca los primos secretos p:";
    std::cin >> p;
    std::cout << ">> q:";
    std::cin >> q;
    int forP = 0;
    while(forP == 0) {
        if(isPrimo(p) && (isPrimo(q))) {
            std::cout << ">> p y q son valores primos." << std::endl;
            _n = p * q;
            std::cout << ">> n = p * q = " << _n;
            forP = 1;
        }else if(isPrimo(p)) {
            std::cout << ">> p es un numero primo, pero q no." << std::endl;
            std::cout << ">> Por favor, vuelva a introducir el valor de q(un numero primo):";
            std::cin >> q;
        }else if(isPrimo(q)){
            std::cout << ">> q es un numero primo, pero p no." << std::endl;
            std::cout << ">> Por favor, vuelva a introducir el valor de p(un numero primo):";
            std::cin >> p;
        }
    }
    //Compromiso secreto de A
    int r;
    std::cout << "\n\n>> Introduzca un entero aleatorio r:";
    std::cin >> r;

    int signoS;
    std::cout << "\n>> Elige un signo aleatorio s∈{+1, -1}:";
    std::cin >> signoS;
    int i = 0;
    while(i == 0) {
        if((signoS == -1) || (signoS == 1)) {
            if(signoS == 1) {
                std::cout << ">> Signo aleatorio s = +" << signoS;
            }else {
                std::cout << ">> Signo aleatorio s = " << signoS;    
            }
            i = 1;
        }else{
            std::cout << ">> Signo aleatorio tiene que ser {+1 or -1}\n";
            std::cout << ">> Vuelva a introducir un signo aleatorio:";
            std::cin >> signoS;
        }
    }

    //Identificacion secreta de A
    std::vector<int> vecS;
    std::string s;
    int pos = 0;
    int a = 0;
    int bucle = 0;
    std::cout << "\n\n>> Introduzca S[] para la identificacion secreata de A, y si desea parar(escribe no).\n";
    
    while(bucle == 0) {
        std::cout << "s[" << pos << "] = ";
        std::cin >> s;    
        if(s == "no") {
            bucle =1;
        }else{
            a = stoi(s);
            vecS.push_back(a);
            pos++;
        }
    }
    
    std::cout << ">> Identificacion secreta de A:";
        for(auto s:vecS) {
            std::cout << s << ", ";
        }
    std::cout << std::endl;

    //Identificacion publica de A
    std::vector<int> vecV;
    int v;
    for(int i = 0; i < vecS.size(); i++) {
        v = myPow(vecS[i], 2, _n);
        vecV.push_back(v);
    }

    std::cout << "\n>> Identificacion publica de A."
              << "\n>> v[i] = s[i]^2(mod n)\n"
              << ">> v[]: ";
        for(auto v:vecV) {
            std::cout << v << ", ";
        }
    std::cout << std::endl;

    //Testigo: A envia a B
    std::cout << "\n>> Testigo de A envia a B."
              << "\n>> x = s * r^2";
    int x = signoS * pow(r, 2);
    if(x < 0) {
            x = abs(x) % _n;
            x = (-x) + _n;
    }else{
            x = x % _n;
    }

    std::cout << "\n>> x = " << x;
    
    //Reto: B envia a A
    std::cout << "\n\n>> Reto que envia de B a A";
    int A;
    std::cout << "\n>> Introduzca bit a[]:\n";
    int pos1 = 0;
    std::vector<int> vecA;
    for(int i = 0; i < vecS.size(); i++) {
        std::cout << "bits a[" << pos1 << "] = ";
        std::cin >> A;
        vecA.push_back(A);
    }
    std::cout << ">> bits a[] = ";
    for(auto v:vecA) {
            std::cout << v << ", ";
        }
        std::cout << std::endl;

    //Respuesta: A envia a B
    std::cout << "\n>> Respuesta enviada de A a B"
              << "\n>> y = (r * (s1^a1) * (s2^a2) * (sk^ak)) mod n.";
    int y = r;
    for(int i = 0; i < vecS.size(); i++) {
        int temp = 0;
        temp = pow(vecS[i], vecA[i]);
        y *= temp; 
    }
    y = myPow(y, 1, _n);
    std::cout << "\n>> y = " << y << std::endl;

    //Verificacion B comprueba la respuesta
    std::cout << "\n>> Comproba la respues de A."
              << "\n>> R = y^2 mod n"
              << "\n>> R_A = x * (v[i]^a[i])";
        int R_A = myPow(y, 2, _n);
        std::cout << "\n>> R_A = " << R_A;
        int R_B = x;
            for(int i = 0; i < vecV.size(); i++) {
                int temp1 = 0;
                temp1 = pow(vecV[i], vecA[i]);
                R_B *= temp1;
            }
        R_B = myPow(R_B, 1, _n);
        std::cout << "\n>> R_B = " << R_B;
        if(R_A == R_B) {
            std::cout << "\n>> La identidad de A es correcta.\n";
        }else {
            std::cout << "\n>> La identidad de A es falsa.\n";
        }
    
    std::cout << "\n-----------------Saliendo al algoritmo de Feige-Fiat-Shamir-----------------\n\n";
    
}




//Comprobar que si es un numero primo
inline bool ffa::isPrimo(int numero) {
  // Casos especiales
  if (numero == 0 || numero == 1 || numero == 4) return false;
    for (int x = 2; x < numero / 2; x++) {
      if (numero % x == 0) return false;
    }
  // Si no se pudo dividir por ninguno de los de arriba, sí es primo
  return true;
}


inline int ffa::myPow(int a, int b, int m) {
    //v1 = a^2 mod n
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