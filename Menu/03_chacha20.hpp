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

class chacha20
{
private:
    uint8_t char_to_uint[256];
    const char uint_to_char[10 + 26 + 1] = "0123456789abcdefghijklmnopqrstuvwxyz";
    typedef std::vector<uint8_t> Bytes;
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
    void Chacha20Block(uint8_t*, uint8_t*, uint32_t);
    void Ronda(uint32_t const);
    uint32_t state[16];
    static uint32_t pack4(const uint8_t *);
    uint32_t rotl32(uint32_t, int);
    void lookupTable();
    void Ronda(uint32_t const s[16]); 
    //void Chacha20Block(uint8_t,  uint8_t,  uint32_t);
public:
    chacha20();
    ~chacha20();
    void algoritmo();
    void algoritmo1();
};
