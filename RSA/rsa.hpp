#ifndef RSA_H
#define RSA_H
#define N_ALFABETO 26
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

class RSA {

private:
    //value
    int _eulerValue;
    int _e;
    std::vector<int> _r;
    int _base;
    int _power;
    int _mod;
    std::vector<int> _m;

    //Metodos
    bool isPrimer(int);
    int calculate_eulerValue(int, int);
    int calculate_e(int);
    void blockValue(std::string, int);
    double encrypt(int, int);
    int montgomery();
public:
    RSA();
    ~RSA();
    void algorithm();
    
};

#endif