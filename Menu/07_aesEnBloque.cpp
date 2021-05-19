#include <iostream>
#include "07_aesEnBloque.hpp"

void aesEnBloque::algoritmo() {
    std::cout << "\n--------------------Bienvenido al algoritmo cifrado en bloque-------------------------\n";
    std::cout << "\n>> Que operacion quiere realizar con el algoritmo 'cifrado en bloque'"
              << "\n>> 1. Cifrar con cifrado en bloque"
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
            std::cout << "\n--------------------Saliendo al algoritmo cifrado en bloque-----------------\n\n";
            k = 1;
        }else{
            std::cout << "\n>> No es una opcion, por favor, vuelva a introducir una option:";
            std::cin >> option;
        }
    }
}

void aesEnBloque::algoritmo1(){
    
    uint8_t key[AES_BLOCK_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];
    uint8_t b1[AES_BLOCK_SIZE];
    uint8_t b2[AES_BLOCK_SIZE];
    uint8_t buffer[BUFFER_SIZE];

    //Para hacer proba de resultado más facil
    /*uint8_t key[AES_BLOCK_SIZE] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t iv[AES_BLOCK_SIZE]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t b1[AES_BLOCK_SIZE]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t b2[AES_BLOCK_SIZE]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t buffer[BUFFER_SIZE];*/

    printf("\n------------------Bienvenido al algoritmo AES(Modo CBC)-----------------------\n\n");
    
    printf("Introduzca la clave de 16 bytes en hexadecmal:\n");
	for(uint8_t i = 0; i < 16; i++) {
		printf("KEY_bytes[%d]:",i);
		scanf("%2hhxx", key+i);
	}

    printf("\nIntroduzca IV de 16 bytes en hexadecmal:\n");
	for(uint8_t i = 0; i < 16; i++) {
		printf("IV_bytes[%d]:",i);
		scanf("%2hhxx", iv+i);
	}

    printf("\nIntroduzca el texto original de Bloque 1 de 16 bytes en hexadecmal:\n");
	for(uint8_t i = 0; i < 16; i++) {
		printf("Bloque_1_bytes[%d]:",i);
		scanf("%2hhx", b1+i);
	}
    
    printf("\nIntroduzca el texto original de Bloque 2 de 16 bytes en hexadecmal:\n");
	for(uint8_t i = 0; i < 16; i++) {
		printf("Bloque_2_bytes[%d]:",i);
		scanf("%2hhx", b2+i);
	}

    //Key
	printf("Clave: ");
    for(int i = 0; i < 16; i++) {
        printf("%.2x ", key[i]);
    }
    
    //Iv
    printf("\nIV: ");
    for (int i = 0; i < 16; i++) {
        printf("%.2x ", iv[i]);
	}

    //B1 testo original
    printf("\nB1 testo original: ");
    for (int i = 0; i < 16; i++) {
        printf("%.2x ", b1[i]);
	}

    //B2 testo original
    printf("\nB2 testo original: ");
    for (int i = 0; i < 16; i++) {
        printf("%.2x ", b2[i]);
	}
    printf("\n");


    //Cifrar
    printf("Bloque 1 de Texto Cifrado: ");
    AES128_CBC_encrypt_buffer(buffer, b1, 64, key, iv);

    printf("Bloque 2 de Texto Cifrado: ");
    AES128_CBC_encrypt_buffer(buffer, b2, 64, key, iv);

    //Descifrar
    //AES128_CBC_decrypt_buffer(buffer, b1+16, 16, key, iv);

    }