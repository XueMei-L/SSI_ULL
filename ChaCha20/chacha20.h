#include <stdint.h>

#define ROTL32(v, n) ((v) << (n)) | ((v) >> (32 - (n)))

#define LE(p) (((uint32_t)((p)[0])) | ((uint32_t)((p)[1]) << 8) | ((uint32_t)((p)[2]) << 16) | ((uint32_t)((p)[3]) << 24))
#define FROMLE(b, i) (b)[0] = i & 0xFF; (b)[1] = (i >> 8) & 0xFF; (b)[2] = (i >> 16) & 0xFF; (b)[3] = (i >> 24) & 0xFF;

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

typedef struct
{
  uint32_t schedule[16];
  uint32_t keystream[16];
  size_t available;
} chacha20_ctx;

//Call this to initilize a chacha20_ctx, must be called before all other functions
void chacha20_setup(chacha20_ctx *ctx, const uint8_t *key, size_t length, uint8_t nonce[8]);

//Call this if you need to process a particular block number
void chacha20_counter_set(chacha20_ctx *ctx, uint64_t counter);

//Raw keystream for the current block, convert output to uint8_t[] for individual bytes. Counter is incremented upon use
void chacha20_block(chacha20_ctx *ctx, uint32_t output[16]);

//Encrypt an arbitrary amount of plaintext, call continuously as needed
void chacha20_encrypt(chacha20_ctx *ctx, const uint8_t *in, uint8_t *out, size_t length);

//Decrypt an arbitrary amount of ciphertext. Actually, for chacha20, decryption is the same function as encryption
void chacha20_decrypt(chacha20_ctx *ctx, const uint8_t *in, uint8_t *out, size_t length);

#ifdef __cplusplus
}
#endif

