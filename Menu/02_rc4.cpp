/********************************************************************
* AUTHOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSITY: Universidad de La Laguna
* SUBJECT: Seguridad en sistemas informaticos
* VERSION: 2.0
* PRACTICE: 05
* TITLE: The vigenere cipher
* DESCRIPTION: Implement the vigenere cipher
* COMPILATION: make
*              make clean (para eliminar)
* *****************************************************************/

#include <iostream>
#include "02_rc4.hpp"


void rc4::algoritmo() {
    std::cout << "\n--------------------Bienvenido al algoritmo RC4-------------------------\n";
    std::cout << "\n>> Que operacion quiere realizar con el algoritmo 'RC4'"
              << "\n>> 1. Cifrar con RC4"
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
            std::cout << "\n--------------------Saliendo al algoritmo RC4----------------------\n\n";
            k = 1;
        }else{
            std::cout << "\n>> No es una opcion, por favor, vuelva a introducir una option:";
            std::cin >> option;
        }
    }
}

void rc4::algoritmo1() {
    printf("\n------------------------Bienvenido al algoritmo de RC4------------------------\n");
    //definir por defecto
    unsigned char s[256] = { 0 }, s2[256] = { 0 };
    char key[256] = {2,5};
    char msg[512] = {1,34};
    unsigned long len = strlen(msg);
    
    //Inicializacion
    rc4_init(s, (unsigned char*)key, strlen(key));
    printf("\n>> El sistema inicializado la tabla\n");
    //Pasar a hexadecimal
        for(int i = 0; i < 256; i++)
        {
            printf("%02X", s[i]);                       //cambiar deciamar a hexadecimal
            if (i && (i + 1) % 16 == 0)putchar('\n');
        }
        printf("\n");

        //usamos S2 para guardar la inicializacion de s[i]
        for(int i = 0; i < 256; i++)
        {
            s2[i] = s[i];
        }

    //Salida por la pantalla
    printf("\n>> El sistema ha terminado de inicializar la tabla.");
    printf("\n>> Ahora es el proceso de cifrar con el metodo RC4.");
    printf("\n>> El mensaje despues de cifrar con el metodo RC4 es: ");
    rc4_crypt(s, (unsigned char*)msg, len);             //Cifrar
    printf("\n>> Ya hemos terminado el proceso de cifrar, ahora desciframos el mensaje ---\n");
    printf("\n>> El mensaje original es:");
    rc4_crypt(s2, (unsigned char*)msg, len);            //Descifrar
    printf("\n>>Hemos realizado todos los procesos con el metodo RC4 ---\n");
    std::cout << "\n--------------------Saliendo al algoritmo RC4----------------------\n\n";
}