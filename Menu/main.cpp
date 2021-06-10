#include <iostream>
#include "01_cv.hpp"
#include "02_rc4.hpp"
#include "03_chacha20.hpp"
#include "04_cagps.hpp"
#include "05_snow3gyaes.hpp"
#include "06_aes.hpp"
#include "07_aesEnBloque.hpp"
#include "08_diffie_hellman_elgamal.hpp"
#include "09_rsa.hpp"
#include "10_eliptic.hpp"
#include "11_ffa.hpp"

int main() {
    std::string name;
    std::cout << ">> Please enter your name:";
    std::cin >> name;
    std::cout << ">> Hello, " << name;
    std::cout << "\n>> Welcome to the world of Computer Systems Security\n";
    int option = 0;
    while(option == 0){
    std::cout << ">> Indicates which algorithm do you want to use?\n"
              << ">> 01. Vigenere\n"
              << ">> 02. Rc4\n"
              << ">> 03. Chacha20\n"
              << ">> 04. C/A de GPS\n"
              << ">> 05. SNOW 3G y AES\n"
              << ">> 06. AES\n"
              << ">> 07. Modos de cifrado en bloque\n"
              << ">> 08. Cifrado de ElGamal\n"
              << ">> 09. RSA\n"
              << ">> 10. Diffie-Hellman y ElGamal Elipticos\n"
              << ">> 11. Feige-FiatShamir\n"
              << ">> 12. Salir al program\n"
              << ">> Your opcion es:";
    std::cin >> option;
        switch(option) {
            case 1: {
                Vigenere_Cipher * ptr_obj01 = new Vigenere_Cipher();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 2: {
                rc4 * ptr_obj01 = new rc4();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 3: {
                chacha20 * ptr_obj01 = new chacha20();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 4: {
                CAGPS * ptr_obj01 = new CAGPS();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 5: {
                SNOW3GYAES * ptr_obj01 = new SNOW3GYAES();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 6: {
                aes * ptr_obj01 = new aes();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 7: {
                aesEnBloque * ptr_obj01 = new aesEnBloque();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 8: {
                DH_GM * ptr_obj01 = new DH_GM();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 9: {
                RSA * ptr_obj01 = new RSA();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 10: {
                Eliptica * ptr_obj01 = new Eliptica();
                ptr_obj01->algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }

            case 11: {
                ffa * ptr_obj01 = new ffa();
                ptr_obj01 -> algoritmo();
                delete ptr_obj01;
                option = 0;
                break;
            }
            case 12: {
                option = 1;
                std::cout << ">> Good Bye, " << name << std::endl;
                break;
            }
            
            default: {
                std::cout << ">> This is an option available, please choose an option again.\n";
                option = 0;
                break;
            }
        }
    }
}