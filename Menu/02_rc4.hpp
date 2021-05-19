#include <stdio.h>
#include <string.h>

class rc4
{
private:

    /*Inicializacion de la tabla*/
    void rc4_init(unsigned char*s, unsigned char*key, unsigned long Len)
    {
        int i = 0, j = 0;
        char k[256] = { 0 };
        unsigned char tmp = 0;
        for (i = 0; i < 256; i++)
        {
            s[i] = i;
            k[i] = key[i%Len];
        }
        for (i = 0; i < 256; i++)
        {
            j = (j + s[i] + k[i]) % 256;
            tmp = s[i];                 //Realizar el intercambio de valores
            s[i] = s[j];
            s[j] = tmp;
        }
    }
    /*RC4 para cifrar*/
    void rc4_crypt(unsigned char*s, unsigned char*Data, unsigned long Len)
    {
        int i = 0, j = 0, t = 0;
        unsigned long k = 0;
        unsigned char tmp;
        for (k = 0; k < Len; k++)
        {
            i = (i + 1) % 256;
            j = (j + s[i]) % 256;
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            t = (s[i] + s[j]) % 256;
            Data[k] ^= s[t];                        //Asignación después de XOR bit a bit
            printf("%d ",Data[k]);
        }

    }
    void algoritmo1();
public:
    rc4(/* args */){}
    ~rc4(){}
    void algoritmo();
};
