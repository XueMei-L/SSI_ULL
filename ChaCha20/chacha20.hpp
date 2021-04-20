#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stddef.h>
#include <stdint.h>

#define CHACHA20_QUARTERROUND(x, a, b, c, d) \
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 16); \
    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 12); \
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 8); \
    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 7);
#define ROUNDS 20

uint8_t char_to_uint[256];
const char uint_to_char[10 + 26 + 1] = "0123456789abcdefghijklmnopqrstuvwxyz";
typedef std::vector<uint8_t> Bytes;
Bytes hex_to_raw(const Bytes &);
Bytes str_to_bytes(const char *);
void Chacha20Block(uint8_t, uint8_t, uint32_t);
void Ronda(uint32_t const);
uint32_t state[16];


static uint32_t pack4(const uint8_t *a){
    return
        uint32_t(a[0] << 0*8) |
        uint32_t(a[1] << 1*8) |
        uint32_t(a[2] << 2*8) |
        uint32_t(a[3] << 3*8);
}

static uint32_t rotl32(uint32_t x, int n){
    return (x << n) | (x >> (32 - n));
}

void lookupTable(){
    // Initialize lookup table
    for (int i = 0; i < 10; i++) char_to_uint[i + '0'] = i;
    for (int i = 0; i < 26; i++) char_to_uint[i + 'a'] = i + 10;
    for (int i = 0; i < 26; i++) char_to_uint[i + 'A'] = i + 10;
}

void Ronda(uint32_t const s[16]) {
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

void Chacha20Block(uint8_t key[32],  uint8_t nonce[24],  uint32_t count){
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


Bytes str_to_bytes(const char *src){
    return Bytes(src, src + strlen(src));
}

Bytes hex_to_raw(const Bytes &src){
    size_t n = src.size();
    assert(n % 2 == 0);
    Bytes dst(n/2);
    for (size_t i = 0; i < n/2; i++){
        uint8_t hi = char_to_uint[src[i*2 + 0]];
        uint8_t lo = char_to_uint[src[i*2 + 1]];
        dst[i] = (hi << 4) | lo;
    }
    return dst;
}