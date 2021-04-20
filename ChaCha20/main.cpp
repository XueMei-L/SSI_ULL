#include "chacha20.hpp"
#include <iostream>


int main() {
    
    printf("--------------------Bienvenido al algoritmo Chacha20-------------------------");
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

    printf("-----------------------Fin del algoritmo Chacha20----------------------------\n");

}
