#include "ecliptic.hpp"



Ecliptic::Ecliptic(){}

Ecliptic::~Ecliptic(){}

void Ecliptic::saveData() {
/*
  //Para el caso del valor primo p
  caseP();

  //Para preguntar los valores de a y b
  caseAB();

  //Para comprobar el punto base G que pertenece a los puntos de la curca
  curvePoints();
  caseG();
  

  //Para pedir la clave privada de Bob dB y de Alice dA
  casedBdA();
  
  //Para preguntar el mensaje original y obtener M y h
  caseMsg();*/
  
  //Calcular valor Euclide
  _p = 7;
  _a = 3;
  _dB = 2;
  _Gx = 3;
  _Gy = 5;
/*  int x3_A = 0;
  int y3_B = 0;
  int x3_B = 0;
  int y3_A = 0;
*/
  //Clave pública de B: punto dBG=(9,7)
  std::cout << "Clave publica de B = _dB * G(" << _Gx << ", " << _Gy << "):";
  int x1_dB, y1_dB, x2_dB, y2_dB, x3_dB, y3_dB;
  if(_dB % 2 == 0) {
    x1_dB = _Gx;
    x2_dB = _Gx;
    y1_dB = _Gy;
    y2_dB = _Gy;
    calculateLambdaAndNewPoints(x1_dB, y1_dB, x2_dB, y2_dB, x3_dB, y3_dB);
  }
  //calculateLambdaAndNewPoints()
  //Clave pública de A: punto dAG=(9,6)
  //int x1_dA, y1_dA, x2_dA, y2_dA, x3_dA, y3_dA;
}



/**
 * Para preguntar datos sobre el valor primo P
*/
void Ecliptic::caseP() {
  //Para el caso del valor primo p
  std::cout << ">> Introduzca el valor de P (valor primo > 3): ";
  std::cin >> _p;
  int forP = 0;
  while(forP == 0) {
    if(isPrimo(_p) && (_p > 3)) {
      std::cout << "Has introducido un numero primo." << std::endl;
      forP = 1;
    }else{
      std::cout << "Por favor, vuelva a introducir un numero primo:";
      std::cin >> _p;
    }
  }
  std::cout << std::endl;
}


/**
 * Pedir los valores de a y b y comprobar que son validos
*/
void Ecliptic::caseAB() {
  std::cout << ">> Introduzca el valor de a y b separado por el espacio:";
  std::cin >> _a >> _b;
  int forAB = 0;
    while(forAB == 0) {
    if(isOk(_a) && isOk(_b)) {
      std::cout << "Los numeros introducido son validos." << std::endl;
      forAB = 1;
    }else if(isOk(_a)) {
      std::cout << "El valor de b es no es valido, vuelva a introducir por favor:";
      std::cin >> _b;
    }else if(isOk(_b)) {
      std::cout << "El valor de a es no es valido, vuelva a introducir por favor:";
      std::cin >> _a;  
    }else {
      std::cout << "Los dos numeros son invalidos, vuelva a intrdocuri los dos numeros por favor:";
      std::cin >> _a >> _b;
    }
  }
  std::cout << std::endl;
}


/**
 * Para oedir un punto base
 * comprobar que dicho punto pertenece a los puntos de la curva
*/
void Ecliptic::caseG() {
  std::cout << ">> Introduzca punto x e y del punto base, separado por espacio:";
  std::cin >> _Gx >> _Gy;
  while(!isIn()) {
    std::cout << "G(" << _Gx << ", " << _Gy << ") no pertenece a los puntos de la curva"
                                            << "vuelva a poner un punto:";
    std::cin >> _Gx >> _Gy;
  }
  std::cout << "G(" << _Gx << ", " << _Gy << ") pertenece a los puntos de la curva" << std::endl;
  std::cout << std::endl;
}


/**
 * Para pedir la clave privada de Bob dB y de Alice dA y comprobar que son validos
*/
void Ecliptic::casedBdA() {
  std::cout << ">> Introduzca el valor de la clave privada de Bob y de Alice separado por el espacio:";
  std::cin >> _dB >> _dA;
  int fordBdA = 0;
    while(fordBdA == 0) {
    if(isOk(_dA) && isOk(_dB)) {
      std::cout << "Las dos claves privadas son validas." << std::endl;
      fordBdA = 1;
    }else if(isOk(_dA)) {
      std::cout << "La clave privada de Bob no es valido, vuelva a introducir por favor:";
      std::cin >> _dB;
    }else if(isOk(_dB)) {
      std::cout << "La clave privada de Alice no es valido, vuelva a introducir por favor:";
      std::cin >> _dA;  
    }else {
      std::cout << "Las dos claves privadas no son validas, vuelva a intrdocuri por favor (orden: Bob, Alice):";
      std::cin >> _dB >> _dA;
    }
  }
  std::cout << std::endl;
}


/**
 * Preguntar sobre el mensaje que quiere enviar, y obtener el valor de M y h
*/
void Ecliptic::caseMsg() {
  std::cout << ">> Introduzca el mensaje original:";
  std::cin >> _m;

  //Codificar el mensaje m
  int length = codificarM(_m);
  _M = pow(2, length);
  std::cout << "M = " << _M << std::endl;

  //Para calcular el valor de H mediante M
  _h = _p / _M;
  std::cout << "h = " << _h << "<" << _p << "/" << _M << std::endl;
  std::cout << std::endl;
}


/**
 * m en decimal codificado como una ristra binaria tq 0 < m < M
*/
int Ecliptic::codificarM(int n)
{
    std::string M;
    while (n != 0){
        M += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }

    // Comprobar que m es entre 0 y M
    return M.size();
}


/**
 * Identificar que si es un numero primo o no
*/
bool Ecliptic::isPrimo(int numero) {
  // Casos especiales
  if (numero == 0 || numero == 1 || numero == 4) return false;
    for (int x = 2; x < numero / 2; x++) {
      if (numero % x == 0) return false;
    }
  // Si no se pudo dividir por ninguno de los de arriba, sí es primo
  return true;
}


/**
 * Identificar que si los valores de a y b cumplen las condiciones necesarias
 * 0 < a, b < p
 * a y b pertenecen la curva ecliptica
 * y2 = x3 + ax + b
 * p es el valor primo
*/
bool Ecliptic::isOk(int num) {
  if(num > 0 && num < _p) {
    return true;
  }
  return false;
}


/**
 * Calcular los puntos de la curva que pertenece la siguiente ecuacion
 * y2 = x3 + ax + b
*/
void Ecliptic::curvePoints() {
  int rightEquation = 0;
  int leftEquation = 0;
  int pos = 0;
  for(int i = 0; i < _p; i++) {
    rightEquation = pow(i, 3);
    rightEquation += _a * i + _b;
    rightEquation = rightEquation % _p;
    for(int j = 0; j < _p; j++) {
      leftEquation = pow(j, 2);
      leftEquation = leftEquation % _p;
      if(rightEquation == leftEquation) {
        P* points = new P { i,
                            j
                          };
        
        pos++;
        _points.push_back(points);
      }
    }
  }

  /*std::cout << "Puntos de la curva: ";
  for(int i = 0; i < _points.size(); i++) {
      std::cout << "(" << _points.at(i)->i << ", " << _points.at(i)->j << ") ";
  }*/
}


/**
 * Comprobar que el punto base pertenece a los puntos de la curva
 * (Gx, Gy) ∈ Puntos de la curva
*/
bool Ecliptic::isIn(){
  for(int i = 0; i < _points.size(); i++) {
    if((_Gx == _points.at(i)->i) && (_Gy == _points.at(i)->j)) {
      return true;
    }
  }
  return false;
}


/**
 *  Calcular el valor de Lambda cada vez que sea necesaria 
*/
void Ecliptic::calculateLambdaAndNewPoints(int x1, int y1, int x2, int y2, int& x3, int& y3) {
  int lambda;
  int lambdaNumerator;
  int lambdaDenominator;
  if( (x1 ==  x2) && (y1 == y2) ) {
    lambdaNumerator = pow(x1, 2);
    lambdaNumerator = (3 * lambdaNumerator + _a);
    lambdaDenominator = (2 * y1);
  }else {
    lambdaNumerator = y2 - y1;
    lambdaDenominator = x2 - x1;
  }
  if(lambdaNumerator % lambdaDenominator == 0) {
    lambda = lambdaNumerator / lambdaDenominator;
  }else{
    lambdaDenominator = valueEucler(lambdaDenominator);
    lambda = lambdaNumerator * lambdaDenominator % _p;
  }


  std::cout << "lambda = " <<  lambda <<  std::endl;

  //calcular x3 e y3
  x3 = pow(lambda, 2);
  x3 = x3 - x1 - x2;
  if(x3 < 0) {
    x3 = abs(x3) % _p;
    x3 = (-x3) + _p;
  }

  y3 = lambda * (x1 - x3) - y1;
  if(y3 < 0) {
    y3 = abs(y3) % _p;
    y3 = (-y3) + _p;
  }


  std::cout << "x3 = " << x3 << std::endl;
  std::cout << "y3 = " << y3 << std::endl;
}


/**
 * Calcular el valor de euclide solo en el caso de que lamda es una fraccion
*/
inline int Ecliptic::valueEucler(int denominator) {
        int b = _p;
        int x = 1, y = 0;
        int xLast = 0, yLast = 1;
        int q, r, m, n;
        while (denominator != 0) {
            q = b / denominator;
            r = b % denominator;
            m = xLast - q * x;
            n = yLast - q * y;
            xLast = x, yLast = y;
            x = m, y = n;
            b = denominator, denominator = r;
        }
        if(xLast < 0) {
          xLast = xLast + _p;
        }
        //std::cout << "xlast = "<< xLast;
        return xLast;
}