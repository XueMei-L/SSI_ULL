/******************************************************************************************
 * AUTHOR: XueMei Lin
 * DATE: 07/03/2021
 * EMAIL: alu0101225845@ull.edu.es
 * GITHUB: XueMei-L
 * UNIVERSITY: Universidad de la laguna
 * DEGREE: Computer engineering degree
 * SUBJECT: Seguridad en sistemas informaticos
 * PRACTICENUM: 2
 * VERSION: 2.0
 * TITLE: RC4
 * COMPILATION: gcc -o main main.c
 * DESCRIPTION: to cipher a text.
 * *****************************************************************************************/

#include <stdio.h>
#include <string.h>

void rc4_init(unsigned char*, unsigned char*, unsigned long);
void rc4_crypt(unsigned char*, unsigned char*, unsigned long );

int main()
{
    //definir por defecto
    unsigned char s[256] = { 0 }, s2[256] = { 0 };
    char key[256] = {2,5};
    char msg[512] = {1,34};
    unsigned long len = strlen(msg);
 
    //Inicializacion
    rc4_init(s, (unsigned char*)key, strlen(key));
    printf("-- Hemos empezamos de realizar la inicializacion ---：\n\n");

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
    printf("-- Hemos terminado de realizar la inicializacion ---:\n\n");
    printf("-- Ahora es el proceso de cifrar con el metodo RC4 ---:\n\n");
    printf("El mensaje despues de cifrar con el metodo RC4 es: ");
    rc4_crypt(s, (unsigned char*)msg, len);             //Cifrar
    printf("\n\n--- Ya hemos terminado el proceso de cifrar, ahora desciframos el mensaje ---\n");
    printf("\nEl mensaje original es:");
    rc4_crypt(s2, (unsigned char*)msg, len);            //Descifrar
    printf("\n\n--- Hemos realizado todos los procesos con el metodo RC4 ---\n");
    return 0;
}


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
