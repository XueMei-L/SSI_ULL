#include <iostream>
#include <vector>
#include <cmath>

class Ecliptic {

private:
    int _p;
    int _a,  _b;
    int _Gx, _Gy;
    int _dB, _dA;
    int _m;
    int _M;
    int _h;
    struct P{
        int i;
        int j;
    };

    std::vector<P*> _points;

    void caseP();
    void caseAB();
    void caseG();
    void casedBdA();
    void caseMsg();
    inline bool isPrimo(int);          //Comprobar que si es un numero primo
    inline bool isOk(int);             //Comprobar que a y b cumplen las condiciones
    inline void curvePoints();
    inline bool isIn();
    inline int codificarM(int);
    inline void calculateLambdaAndNewPoints(int, int, int, int, int&, int&);
    inline int valueEucler(int);

public:
    Ecliptic();
    ~Ecliptic();
    void saveData();
};

