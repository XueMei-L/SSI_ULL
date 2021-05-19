#include <iostream>
#include <vector>
#include <cmath>

class Eliptica{

private:
    int _p;
    int _a,  _b;
    int _Gx, _Gy;
    int _dB, _dA;
    int _m;
    int _M;
    int _h;
    int _Key_dA_x3;
    int _Key_dA_y3;
    int _Key_dB_x3;
    int _Key_dB_y3;
    int _QmX;
    int _QmY;
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
    void calculateLambdaAndNewPoints(int, int, int, int, int&, int&);
    inline int valueEucler(int);
    void keyPoints(int, int, int, int ,int);
    void keyPoints2(int, int, int, int ,int);
    void Qm();
    void FinalResult();
public:
    Eliptica();
    ~Eliptica();
    void saveData();
    void algoritmo();
};

