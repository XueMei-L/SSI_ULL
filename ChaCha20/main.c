/*
 * La idea principal es construir Keystream y luego hacer la operacion de cifrar
 * 256 bits de clave
 * 32 bits de contador 
 * 96 bits de none
 * 1. Formar Keystream
 * 2. Hacer cambio de columa y diagonal y despues la operacion de QuaterRound (10 iteraciones)
 * 3. Keystrem + msg = text cifrado
 * */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <alloca.h>
#include "chacha20.h"


void hex2byte(const char *hex, uint8_t *byte)
{
  while (*hex) { sscanf(hex, "%2hhx", byte++); hex += 2; }
}

void test_keystream(const char *text_key, const char *text_nonce, const char *text_value, unsigned int number)
{
  chacha20_ctx ctx;
  uint32_t output[16];
  unsigned int i = 0;
  uint8_t key[32];
  uint8_t nonce[8];
  size_t value_len = strlen(text_value) / 2;
  uint8_t *value = alloca(value_len);

  printf("Comprobacion de: Keystream #%u: ", number);

  hex2byte(text_key, key);
  hex2byte(text_nonce, nonce);
  hex2byte(text_value, value);
  chacha20_setup(&ctx, key, sizeof(key), nonce);

  while (i < value_len)
  {
    chacha20_block(&ctx, output);
    if (memcmp(output, value+i, MIN(sizeof(output), value_len-i)))
    {
      puts("Error");
      return;
    }
    i += sizeof(output);
  }
  puts("Correctamente");
}

void test_encipherment(const char *text_key, const char *text_nonce, const char *text_plain, const char *text_cipher, uint64_t counter, unsigned int number)
{
  chacha20_ctx ctx;
  size_t i = 0;
  uint8_t key[32];
  uint8_t nonce[8];
  size_t len = strlen(text_plain) / 2;
  uint8_t *plain = alloca(len);
  uint8_t *cipher = alloca(len);
  uint8_t *output = alloca(len);

  printf("Comprobacion de #%u: ", number);

  hex2byte(text_key, key);
  hex2byte(text_nonce, nonce);
  hex2byte(text_plain, plain);
  hex2byte(text_cipher, cipher);
  chacha20_setup(&ctx, key, sizeof(key), nonce);

  //Prueba de longitud exacta
  memset(output, 0, len);
  chacha20_counter_set(&ctx, counter);
  chacha20_encrypt(&ctx, plain, output, len);
  if (memcmp(output, cipher, len))
  {
    puts("Failed exact length");
    return;
  }
  //Longuitud fija
  while (i < len)
  {
    size_t j;
    ++i;
    memset(output, 0, len);
    chacha20_counter_set(&ctx, counter);
    for (j = 0; j < len; j += i)
    {
      chacha20_encrypt(&ctx, plain+j, output+j, MIN(i, len-j));
    }
    if (memcmp(output, cipher, len))
    {
      printf("Failed at round: %zu\n", i);
      return;
    }
  }
  //Random length tests
  for (i = 0; i < 1000; ++i)
  {
    size_t amount, j;
    memset(output, 0, len);
    chacha20_counter_set(&ctx, counter);
    for (j = 0; j < len; j += amount)
    {
      amount = rand() & 15;
      chacha20_encrypt(&ctx, plain+j, output+j, MIN(amount, len-j));
    }
    if (memcmp(output, cipher, len))
    {
      puts("Failed random tests 1");
      return;
    }
  }
  //Random length tests 2
  for (i = 0; i < 1000; ++i)
  {
    size_t amount, j;
    memset(output, 0, len); 
    chacha20_counter_set(&ctx, counter);
    for (j = 0; j < len; j += amount)
    {
      amount = 65 + (rand() & 63);
      chacha20_encrypt(&ctx, plain+j, output+j, MIN(amount, len-j));
    }
    if (memcmp(output, cipher, len))
    {
      puts("Failed random tests 2");
      return;
    }
  }
  puts("Correctamente");
}

int main()
{
  //Keystream - key - none - text - keystream nª
  test_keystream("0000000000000000000000000000000000000000000000000000000000000000", "0000000000000000", "76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586", 1);
  test_keystream("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f", "0001020304050607", "f798a189f195e66982105ffb640bb7757f579da31602fc93ec01ac56f85ac3c134a4547b733b46413042c9440049176905d3be59ea1c53f15916155c2be8241a38008b9a26bc35941e2444177c8ade6689de95264986d95889fb60e84629c9bd9a5acb1cc118be563eb9b3a4a472f82e09a7e778492b562ef7130e88dfe031c79db9d4f7c7a899151b9a475032b63fc385245fe054e3dd5a97a5f576fe064025d3ce042c566ab2c507b138db853e3d6959660996546cc9c4a6eafdc777c040d70eaf46f76dad3979e5c5360c3317166a1c894c94a371876a94df7628fe4eaaf2ccb27d5aaae0ad7ad0f9d4b6ad3b54098746d4524d38407a6deb3ab78fab78c9", 2);
  
  //Prueba de cifrado - 
  test_encipherment("0000000000000000000000000000000000000000000000000000000000000000", "0000000000000000", "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", "76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586", 0, 1);
  test_encipherment("1c9240a5eb55d38af333888604f6b5f0473917c1402b80099dca5cbc207075c0", "0000000000000002", "2754776173206272696c6c69672c20616e642074686520736c6974687920746f7665730a446964206779726520616e642067696d626c6520696e2074686520776162653a0a416c6c206d696d737920776572652074686520626f726f676f7665732c0a416e6420746865206d6f6d65207261746873206f757467726162652e", "62e6347f95ed87a45ffae7426f27a1df5fb69110044c0d73118effa95b01e5cf166d3df2d721caf9b21e5fb14c616871fd84c54f9d65b283196c7fe4f60553ebf39c6402c42234e32a356b3e764312a61a5532055716ead6962568f87d3f3f7704c6a8d1bcd1bf4d50d6154b6da731b187b58dfd728afa36757a797ac188d1", 42, 2);
  return(0);
}
