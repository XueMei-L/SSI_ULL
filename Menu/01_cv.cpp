/********************************************************************
* AUTHOR: XueMei Lin
* EMAIL: alu0101225845@ull.edu.es
* UNIVERSITY: Universidad de La Laguna
* SUBJECT: Seguridad en sistemas informaticos
* VERSION: 2.0
* PRACTICE: 05
* TITLE: The vigenere cipher
* DESCRIPTION: Implement the vigenere cipher
* COMPILATION: make
*              make clean (para eliminar)
* *****************************************************************/

/**
 * EXAMPLE: 
 * key word: MISION
 * Original text: ESTE MENSAJE SE AUTODESTRUIRA
 * 
 * ESTEME NSAJES EAUTOD ESTRUI RA   (This is original mensage)
 * MISION MISION MISION MISION MI   (This is key word)
 * QALMAR ZASRSF QIMBCQ QALZIV DI   (This is result)
 * 
 * Texto cifrado: QALMARZASRSFQIMBCQQALZIVDI
*/


/**
 * Include files
*/
#include "01_cv.hpp"

/**
 * Constructor
 * Destroyer
*/
Vigenere_Cipher::Vigenere_Cipher(){}
Vigenere_Cipher::~Vigenere_Cipher(){}


/**
 * Main menu
*/
void Vigenere_Cipher::algoritmo(){
    std::cout << "\n------------------------Welcome to the Vigenere algorithm-------------------" << std::endl;
    std::string result;
    int option;
    int num = 0;
    while(num == 0){
        std::cout << "\n>> What operacion do you want to perform with 'Vigenere Encroyption' method" << std::endl
                  << ">> 1. Encrypt.\n"
                  << ">> 2. Descrypt.\n"
                  << ">> 3. Back to menu" << std::endl;
        std::cout << ">> Your option is:";      
        std::cin >> option;
        if(option == 1) {
            std::string passwd_C;
            std::cout << ">> Tell me a key word:";
            std::cin >> passwd_C;
            std::string originalMsg;
            std::cout << ">> What message do you want to encrypt:";
            std::cin >> originalMsg;    
            Vigenere_encrypt(passwd_C, originalMsg, result);
        }else if(option == 2) {
            std::string msg_Desc;
            std::string passwd_Desc;
            std::string originalMsg;
            std::cout << ">> Tell me a key word:";
            std::cin >> passwd_Desc;
            std::cout << ">> What message do you want to descrypt:";
            std::cin >> msg_Desc;
            Vigenere_decrypt(passwd_Desc, msg_Desc, originalMsg);
        }else {
            std::cout << "\n------------------------Exiting to the Vigenere algorithm-------------------\n" << std::endl;
            num ++;
        }
    }
}

/**
 * Method to encrypt
*/
void Vigenere_Cipher::Vigenere_encrypt(std::string pw, std::string msg, std::string result) {
    
    result.resize(msg.size());
    std::string new_vector;                                     
    for(int i = 0; i < pw.size(); i++) {
        if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i]);
        }else if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i] - 32);
        }else {
            new_vector.push_back(pw[i]);
        }
    }

    int count = 0;
    for(int i = 0; i < msg.size(); i++) {
        if((int)(msg[i] > 64 && (int)(msg[i]) < 91)) {
            result[i] = (char)((((int)msg[i] - 65 + (new_vector[(count++)%new_vector.size()]-'A')) % 26) + 65);
        }else if((int)msg[i] > 96 && (int)msg[i] < 123) {
            result[i] = (char)((((int)msg[i] - 97 + (new_vector[(count++) % new_vector.size()] - 'A')) % 26) + 65);
        }else {
            result[i] = msg[i];
        }
    }

    std::cout << "KEY:         " << pw << std::endl;
    std::cout << "MSG:         ";
    for(int i = 0; i < msg.size(); i++) {
        if((i != 0) && (i % pw.size() == 0)){
            std::cout << " ";
        }
        std::cout << msg[i];
    }
    std::cout << std::endl;

    std::cout << "MSG_ENCRYPT: ";
    for(int i = 0; i < result.size(); i++) {
        if((i != 0) && i % pw.size() == 0){
            std::cout << " ";
        }
        std::cout << result[i];
    }
    std::cout << std::endl;

}

/**
 * Method to descrypt
*/
void Vigenere_Cipher::Vigenere_decrypt(std::string pw, std::string result, std::string msg) {

    msg.resize(result.size());
    std::string new_vector;   
    for(int i = 0; i < pw.size(); i++) {
        if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i]);
        }else if((int)pw[i] > 64 && (int)pw[i] < 91) {
            new_vector.push_back(pw[i] - 32);
        }else {
            new_vector.push_back(pw[i]);
        }
    }

    int count = 0;
    for (int i = 0; i < result.size();i++) {
        if ((int)result[i]>64 && (int)result[i] < 91) {
        msg[i] = (char)((((int)result[i] - 65 + 52 - (new_vector[(count++) % new_vector.size()] - 'A')) % 26) + 65);//减去65-k取模可得到前移k位的ascii（大写） //加26使其非负
        }
        else if ((int)result[i] > 96 && (int)result[i] < 123) {
        msg[i] = (char)((((int)result[i] - 97 + 52 - (new_vector[(count++) % new_vector.size()] - 'A') ) % 26) + 65);//减去97-k取模可得到前移k位的ascii（小写）//加26使其非负
        }
        else {
        msg[i] = result[i];
        }
    }
        std::cout << "KEY:          " << pw << std::endl
                  << "MSG_ENCRYPT:  " << result << std::endl
                  << "MSG_ORIGINAL: " << msg << std::endl << std::endl;
}