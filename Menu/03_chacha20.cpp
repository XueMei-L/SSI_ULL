#include "03_chacha20.hpp"
#include <iostream>
#include <stdio.h>

chacha20::chacha20(/* args */){}
chacha20::~chacha20(){}

void chacha20::algoritmo() {
    std::cout << "\n--------------------Bienvenido al algoritmo Chacha20-------------------------\n";
    std::cout << "\n>> Que operacion quiere realizar con el algoritmo 'Chacha20'"
              << "\n>> 1. Cifrar con Chacha20"
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
            std::cout << "\n--------------------Saliendo al algoritmo Chacha20-----------------\n\n";
            k = 1;
        }else{
            std::cout << "\n>> No es una opcion, por favor, vuelva a introducir una option:";
            std::cin >> option;
        }
    }
}

uint32_t chacha20::pack4(const uint8_t *a){
    return
        uint32_t(a[0] << 0*8) |
        uint32_t(a[1] << 1*8) |
        uint32_t(a[2] << 2*8) |
        uint32_t(a[3] << 3*8);
}

uint32_t chacha20::rotl32(uint32_t x, int n){
    return (x << n) | (x >> (32 - n));
}

void chacha20::lookupTable(){
    // Initialize lookup table
    for (int i = 0; i < 10; i++) char_to_uint[i + '0'] = i;
    for (int i = 0; i < 26; i++) char_to_uint[i + 'a'] = i + 10;
    for (int i = 0; i < 26; i++) char_to_uint[i + 'A'] = i + 10;
}

void chacha20::Ronda(uint32_t const s[16]) {
    uint32_t result[16];
    uint32_t out[16];
    for(int i = 0; i < 16; ++i) {
        result[i] = s[i];
    }

        for (int i = 0; i < 10; i++){
            CHACHA20_QUARTERROUND(result, 0, 4, 8, 12)
            CHACHA20_QUARTERROUND(result, 1, 5, 9, 13)
            CHACHA20_QUARTERROUND(result, 2, 6, 10, 14)
            CHACHA20_QUARTERROUND(result, 3, 7, 11, 15)

            CHACHA20_QUARTERROUND(result, 0, 5, 10, 15)
            CHACHA20_QUARTERROUND(result, 1, 6, 11, 12)
            CHACHA20_QUARTERROUND(result, 2, 7, 8, 13)
            CHACHA20_QUARTERROUND(result, 3, 4, 9, 14)
        }
        
        printf("\nEstado final tras las 20 iteraciones= \n");
        for (uint32_t i = 0; i < 16; i++) {
            printf("%.8x ", result[i]);
                if((i+1) % 4 == 0) {
                    printf("\n");
                }
        }

        for (int i = 0; i < 16; i++) {
            out[i] = result[i] + s[i];
        }

        printf("\nEstado de salida del generador= \n");
        
        for (uint32_t i = 0; i < 16; i++) {
            printf("%.8x ", out[i]);
                if((i+1) % 4 == 0) {
                    printf("\n");
                }
        }
}

void chacha20::Chacha20Block(uint8_t key[32],  uint8_t nonce[24],  uint32_t count){
        const uint8_t *magic_constant = (uint8_t*)"expand 32-byte k";
        state[ 0] = pack4(magic_constant + 0*4);
        state[ 1] = pack4(magic_constant + 1*4);
        state[ 2] = pack4(magic_constant + 2*4);
        state[ 3] = pack4(magic_constant + 3*4);
        state[ 4] = pack4(key + 0*4);
        state[ 5] = pack4(key + 1*4);
        state[ 6] = pack4(key + 2*4);
        state[ 7] = pack4(key + 3*4);
        state[ 8] = pack4(key + 4*4);
        state[ 9] = pack4(key + 5*4);
        state[10] = pack4(key + 6*4);
        state[11] = pack4(key + 7*4);
        state[12] = count;
        state[13] = pack4(nonce + 0*4);
        state[14] = pack4(nonce + 1*4);
        state[15] = pack4(nonce + 2*4);

        printf("\nEstado inicial=: \n");
        
        for (uint32_t i = 0; i < 16; i++) {
            printf("%.8x ", state[i]);
                if((i+1) % 4 == 0) {
                    printf("\n");
                }
        }
    }

void chacha20::algoritmo1(){
    
    uint8_t key[32];
    uint8_t nonce[12];
    uint32_t count;

    printf("\nIntroduzca Clave de 256 bits en forma de 8 palabras en hexadecimal:\n");
	for(uint8_t i = 0; i < 32; i++) {
		printf("bytes[%d]:",i);
		scanf("%2hhxx", key+i);
	}

	printf("\nIntroduzca Clave de 256 bits en forma de 8 palabras en hexadecimal:\n");
    for(uint8_t i = 0; i < 12; i++) {
		printf("bytes[%d]:",i);
		scanf("%2hhxx", nonce+i);
	}
    
 	printf("\nIntroduzca Contador de 32 bits en forma de 1 palabra en hexadecimal:\n");
	scanf("%u", &count);

    lookupTable();
    Chacha20Block(key, nonce, count);
    Ronda(state);

    printf("-----------------------Saliendo al algoritmo Chacha20----------------------------\n");

}
