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

#include "05_snow3gyaes.hpp"

SNOW3GYAES::SNOW3GYAES(){}
SNOW3GYAES::~SNOW3GYAES(){}

//Function main
int SNOW3GYAES::algoritmo() {
    std::string algoritmo;
    std::string byte1;
    std::string byte2;
    SNOW3GYAES* ptr_snow3gyaes = new SNOW3GYAES();
    std::cout << "\n-------------------------Bienvenido al algoritmo de snow 3G y AES-------------------------" << std::endl;
    int i = 0;
    int choose = 0;
    while (i == 0) {
        std::cout << ">> Introduzca el algoritmo que quieres realizar, o salir del programa introduciendo 'EXIT':" << std::endl;
        std::cout << ">> 1. SNOW_3G\n"
                  << ">> 2. AES\n"
                  << ">> 3. Volver al menu inicial(Pon EXIT)\n"
                  << ">> Su opcion es:";
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
    return 0;
}


/* Choose algorithm SNOW 3G OR AES */
void SNOW3GYAES::snow3gOrAes(std::string algorithm) {
    if(algorithm == "aes" || algorithm == "AES") {
        vecXor = {0, 0, 0, 1, 1, 0, 1, 1};               //1B 00011011
    }else if(algorithm == "SNOW_3G" || algorithm == "snow_3g") {
        vecXor = {1, 0, 1, 0, 1, 0, 0, 1};               //A9 10101001
    }
}

/* Pasar hexadecimal a binario */
void SNOW3GYAES::hexToBin(std::string hexN, int time) {
    std::string s = hexN;
    std::stringstream ss;
    ss << std::hex << s;
    unsigned n;
    ss >> n;
    std::bitset<8> b(n);
    if(time == 0){
        for(int i = b.size()-1; i >= 0; i--) {
            byte1.push_back(b[i]);   
        }
    }
    else if(time == 1) {
        for(int i = b.size()-1; i >= 0; i--) {
            byte2.push_back(b[i]);
        }
    }else {
        for(int i = b.size()-1; i >= 0; i--) {
            vecXor.push_back(b[i]);
        }
    }
}

/* Mostrar vectores */
void SNOW3GYAES::showVector(std::vector<int>& byte){
    for(auto result:byte)
    {
        std::cout << result;
    }
    std::cout << std::endl;
}

/* Function Distributive */
void SNOW3GYAES::algorithm() {
    std::vector<int> vDis(8);
    std::vector<int> byte1Copy;
    std::vector<int> byte2Copy;
    byte2Copy = byte2;

    multiple = {0, 0, 0, 0, 0, 0, 0, 0};
    assert(byte2Copy.size() == vDis.size());
    for(int i = 0; i < byte2Copy.size(); i++) {
        byte1Copy = byte1;
        vDis = {0, 0, 0, 0, 0, 0, 0, 0};
        if(byte2Copy[i] == 1) {
            vDis.at(i) = 1;
            byte2Copy[i] = 0;
            showVector(vDis);
            showVector(byte1Copy);
            int desplazamiento = vDis.size() - i - 1;
            std::cout << "hay que desplazar " << desplazamiento << std::endl;
            for(int j = 0; j < vDis.size(); j++) {
                if(vDis[j] == 1) {
                    //Si el desplazamiento es 0, directamente igual a vector A
                    if(desplazamiento == 0) {
                        for(int k = 0; k < multiple.size(); k++) {
                            multiple[k] ^= byte1Copy[k];
                        }
                        std::cout << "Despues de realizar la operacion ";
                        showVector(byte1Copy);
                    }else{
                        for(int z = 0; z < desplazamiento; z++) {
                            //Si la primera posicion es 0 -> desplazamiento hacia izq
                            if(byte1Copy[0] == 0) {                            
                                for(int k = 0; k < byte1Copy.size()-1; k++) {
                                    byte1Copy[k] = byte1Copy[k + 1];
                                }
                                byte1Copy[byte1Copy.size() - 1] = 0;
                            //Si la primera posicion es 1 -> desplazamiento hacia izq + A9/1B
                            }else {
                                for(int x = 0; x < byte1Copy.size()-1; x++) {
                                    byte1Copy[x] = byte1Copy[x + 1];
                                }
                                byte1Copy[byte1Copy.size() - 1] = 0;
                                for(int y = 0; y < byte1Copy.size(); y++) {
                                    byte1Copy[y] ^= vecXor[y];
                                }  
                            }
                            std::cout << "Despues de realizar la operacion ";
                            showVector(byte1Copy);
                        }
                        //Rsultado xor cada funcion distributiva
                        for(int a = 0; a < multiple.size(); a++) {
                            multiple[a] ^= byte1Copy[a]; 
                        }
                    }
                }
            }
        }
    }
}


/* Printr all vectors */
void SNOW3GYAES::printResult() {
    std::cout << "-----------------------------------------RESULTADO----------------------------------------" << std::endl;
    std::cout << "Primer byte:    ";
    showVector(byte1);
    std::cout << "Segundo byte:   ";
    showVector(byte2);
    std::cout << "Byte Algoritmo: ";
    showVector(vecXor);
    std::cout << "Multiplicacion: ";
    showVector(multiple);
}