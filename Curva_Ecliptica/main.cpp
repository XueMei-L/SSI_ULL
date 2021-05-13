#include <iostream>
#include <vector>
#include <cmath>
#include "ecliptic.hpp"

 
int main() {

    std::cout << "Bienvenido al algorimot 'ecliptica' " << std::endl;
    Ecliptic* ptr_Ecliptic = new Ecliptic();
    ptr_Ecliptic->saveData();

    std::cout << "El programa ya ha terminado. " << std::endl;
    delete ptr_Ecliptic;

    return 0;
}