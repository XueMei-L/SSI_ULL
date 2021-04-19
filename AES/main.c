#include <stdio.h>
#include "aes.h"
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

static inline void ignore_ret() {}

int main(int argc, char *argv[]) {

	uint8_t i, r;
    uint8_t key[16];
    uint8_t plaintext[16];

    printf("Introduzca la clave de 16 bytes en hexadecmal:\n");
	for(i = 0; i < 16; i++) {
		printf("bytes[%d]:",i);
		ignore_ret(scanf("%2hhxx", key+i));
	}

    printf("Introduzca el texto original de 16 bytes en hexadecmal:\n");
	for(i = 0; i < 16; i++) {
		printf("bytes[%d]:",i);
		ignore_ret(scanf("%2hhx", plaintext+i));
	}

	uint8_t ciphertext[AES_BLOCK_SIZE];
	uint8_t roundkeys[AES_ROUND_KEY_SIZE];
	
	printf("\n--------------------Bienvenido al algoritmo AES-------------------------\n\n");

	//Mostrar Clave
	printf("Clave: ");
    for(int i = 0; i < 16; i++) {
        printf("%.2x", key[i]);
    }

	//Mostrar Texto Original
	printf("\nBloque de Texto Original: ");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%.2x", plaintext[i]);
	}
	printf("\n\n");	


	// key schedule
	aes_key_schedule_128(key, roundkeys);
	printf("Round Keys:\n");
	for ( r = 0; r <= AES_ROUNDS; r++ ) {
		printf("R%d   ", r);
		for (i = 0; i < AES_BLOCK_SIZE; i++) {
			printf("%.2x ", roundkeys[r*AES_BLOCK_SIZE+i]);

		}
		printf("\n");
	}
	printf("\n");


	// encryption
	aes_encrypt_128(roundkeys, plaintext, ciphertext);
	printf("\nBloque de Texto Cifrado: ");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%.2x ", ciphertext[i]);
	}

	// decryption
	printf("\n\nAhora vamos a decifrar");
	aes_decrypt_128(roundkeys, ciphertext, ciphertext);
	printf("\nPlain text: ");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%.2x ", ciphertext[i]);
	}
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		if ( ciphertext[i] != plaintext[i] ) { break; }
	}
	printf("\n--------------------------------------------------------------------------\n");
	return 0;
}