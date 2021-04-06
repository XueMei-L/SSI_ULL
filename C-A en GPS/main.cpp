#include "cagps.h"
#include <iostream>

int main(){
    int step;
    std::cout << "------------------------- Bienvenido al generador de C/A en GPS -----------------------" << std::endl;
    std::cout << "Cuantos pasos quieres realizar:";
    std::cin >> step;
    CAGPS* ptr_obj = new CAGPS(); 
    ptr_obj->algoritmo(step);
    delete ptr_obj;
}