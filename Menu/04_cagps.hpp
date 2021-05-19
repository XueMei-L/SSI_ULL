#include <iostream>
#include <vector>

#ifndef CYA_EN_GPS
#define CYA_EN_GPS

class CAGPS 
{
private:
    std::vector<int> Vec_G1;
    std::vector<int> Vec_G2;
    void int_Vec(std::vector<int>&);
    void ShowVec(const std::vector<int>&);
    void deleteLastNumber(std::vector<int>&, int);
    void F_Xor(std::vector<int>&, std::vector<int>&);
    void algoritmo1();
public:
    CAGPS();
    //CAGPS(std::vector<int>);
    ~CAGPS();
    void algoritmo();
};


#endif