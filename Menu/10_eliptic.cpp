#include "10_eliptic.hpp"

Eliptica::Eliptica(){}

Eliptica::~Eliptica(){}

void Eliptica::algoritmo() {

    std::cout << "Bienvenido al algorimot 'Elipticaa' " << std::endl;
    Eliptica* ptr_Eliptica = new Eliptica();
    ptr_Eliptica->saveData();

    std::cout << "El programa ya ha terminado. " << std::endl;
    delete ptr_Eliptica;
}

void Eliptica::saveData() {

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
  caseMsg();
  
  //Mensaje original codificado como punto Qm
  Qm();

  //Imprimir los resultados finales
  FinalResult();

}

/*
 * Imprimir resultado final
 */
void Eliptica::FinalResult() {

  //Clave publica de B
  std::cout << "Clave publica de B = dB * G = "<< _dB << " * (" << _Gx << ", " << _Gy << ") = ";
  keyPoints(_dB, _Gx, _Gy, _Gx, _Gy);

  //Clave publica de A
  std::cout << std::endl << "Clave publica de A = dA * G = "<< _dA << " * (" << _Gx << ", " << _Gy << ") = ";
  keyPoints(_dA, _Gx, _Gy, _Gx, _Gy);
  std::cout << std::endl;

  //Clave secreta de A: _dA * la clave publica de B
  std::cout << "Clave secreta compartida calculada por A = ";
  keyPoints2(_dA, _Key_dB_x3, _Key_dB_y3, _Key_dB_x3, _Key_dB_y3);
  std::cout << std::endl;

  //Clave secreta de B: _dB * la clave publica de A
  std::cout << "Clave secreta compartida calculada por B = ";
  keyPoints2(_dB, _Key_dA_x3, _Key_dA_y3, _Key_dA_x3, _Key_dA_y3);
  std::cout << std::endl;

  //Imprimir M
  std::cout << "M = " << _M << std::endl;

  //Imprimir h
  std::cout << "h = " << _h << "<" << _p << "/" << _M << std::endl;

  //Mensaje original codificado como punto Qm
  std::cout << "Mensaje original codificado como punto Qm = (" << _QmX << ", " << _QmY << ")" << std::endl; 

  //Mensaje cifrado y clave pública enviados de A a B: 
  //{Qm+dA*(dBG), dAG} = {(0,9), (9,6)}
  std::cout << "Mensaje cifrado y clave pública enviados de A a B = ";
  keyPoints2(2, _QmX, _QmY, _Key_dA_x3, _Key_dA_y3);
  std::cout << ", ";
  keyPoints2(_dA, _Gx, _Gy, _Gx, _Gy);
  std::cout << "}" << std::endl;

}


/*
 * Obtener puntos mediantes bits
 * Puntos x =  m * h + j 
 * hasta que encuentra un punto que coiciden con el xi 
 */
void Eliptica::Qm() {
  for(int j = 0; j < _points.size(); j++) {
    int b = _m * _h + j;
    for(int i = 0; i <_points.size(); i++) {
      if(b == _points.at(i)->i) {
      _QmX = _points.at(i)->i;
      _QmY = _points.at(i)->j;
      i = _points.size();
      j = _points.size();
      }
    }
  }
}


/**
 * Para calcular la clave secreta compartida
*/
void Eliptica::keyPoints2(int dN, int x1, int y1, int x2, int y2) {
  int x3, y3;
  int timeA = dN;
  int rest = timeA % 2;
  while(timeA != 1) {
    timeA = timeA / 2;
    calculateLambdaAndNewPoints(x1, y1, x2, y2, x3, y3);
    //std::cout << "x1 = " << x1 << "y1 = " <<y2 <<  "x2 = " << x1 << "y2 = " << y2; 
    if(timeA != 1) {
      x1 = x3;
      x2 = x3;
      y1 = y3;
      y2 = y3;
      x3 = 0;
      y3 = 0;
    }else if(rest == 1){
      x1 = x3;
      x2 = x3;
      x3 = 0;
      y3 = 0;
      calculateLambdaAndNewPoints(x1, y1, x2, y2, x3, y3);
    }
  }
  std::cout << "(" << x3 << ", " << y3 << ")";
    if(dN == _dA) {
      _Key_dB_x3 = x3;
      _Key_dB_y3 = y3;
  }else if(dN == _dB) {
      _Key_dA_x3 = x3;
      _Key_dA_y3 = y3;
  }
}

/**
 * Para calcular los puntos de la clave publica
*/
void Eliptica::keyPoints(int dN, int x1, int y1, int x2, int y2) {
  int x3, y3;
  int timeA = dN;
  int rest = timeA % 2;
  while(timeA != 1) {
    timeA = timeA / 2;
    calculateLambdaAndNewPoints(x1, y1, x2, y2, x3, y3);
    if(timeA != 1) {
      x1 = x3;
      x2 = x3;
      y1 = y3;
      y2 = y3;
      x3 = 0;
      y3 = 0;
    }else if(rest == 1){
      x1 = x3;
      x2 = x3;
      x3 = 0;
      y3 = 0;
      calculateLambdaAndNewPoints(x1, y1, x2, y2, x3, y3);
    }
  }
  if(dN == _dA) {
      _Key_dA_x3 = x3;
      _Key_dA_y3 = y3;
  }else if(dN == _dB) {
      _Key_dB_x3 = x3;
      _Key_dB_y3 = y3;
  }
  std::cout << "(" << x3 << ", " << y3 << ")";
}


/**
 * Para preguntar datos sobre el valor primo P
*/
void Eliptica::caseP() {
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
 * y2 = x3 + ax + b
 * 4 a^3 + 27 b^2 (mod p) != 0 
*/
void Eliptica::caseAB() {
  std::cout << ">> Introduzca el valor de a y b separado por el espacio:";
  std::cin >> _a >> _b;
  int forAB = 0;
  int a = pow(a, 2);
  a += 4;
  int b = pow(b, 2);
  b += 27;
  a = (a + b) % _p;
    while(forAB == 0) {
    if(isOk(_a) && isOk(_b) && (a != 0)) {
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
void Eliptica::caseG() {
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
 * 0 < a, b < p
*/
void Eliptica::casedBdA() {
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
void Eliptica::caseMsg() {
  std::cout << ">> Introduzca el mensaje original:";
  std::cin >> _m;

  //Codificar el mensaje m
  int binary = codificarM(_m);
  _M = pow(2, binary);

  //Para calcular el valor de H mediante M
  _h = _p / _M;
}


/**
 * m en decimal codificado como una ristra binaria tq 0 < m < M
*/
inline int Eliptica::codificarM(int n)
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
inline bool Eliptica::isPrimo(int numero) {
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
 * a y b pertenecen la curva Elipticaa
 * y2 = x3 + ax + b
 * p es el valor primo
*/
inline bool Eliptica::isOk(int num) {
  if(num > 0 && num < _p) {
    return true;
  }
  return false;
}


/**
 * Calcular los puntos de la curva que pertenece la siguiente ecuacion
 * y2 = x3 + ax + b
*/
inline void Eliptica::curvePoints() {
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

    //Salida por pantalla sobre los puntos
    std::cout << ">> Puntos de la curva:";
    for(int i = 0; i < _points.size(); i++) {
      std::cout << "(" << _points.at(i)->i << ", " << _points.at(i)->j << ") ";
    }
    std::cout << std::endl;
}


/**
 * Comprobar que el punto base pertenece a los puntos de la curva
 * (Gx, Gy) ∈ Puntos de la curva
*/
inline bool Eliptica::isIn(){
  for(int i = 0; i < _points.size(); i++) {
    if((_Gx == _points.at(i)->i) && (_Gy == _points.at(i)->j)) {
      return true;
    }
  }
  return false;
}


/**
 *  Calcular el valor de Lambda cada vez que sea necesaria 
 *  Si P = Q :
 *  3 * x1^2 + a / 2 * y1
 * 
 *  Si P != Q :
 *  y2 - y1 / x2 - x1
*/
void Eliptica::calculateLambdaAndNewPoints(int x1, int y1, int x2, int y2, int& x3, int& y3) {
  
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
  //std::cout << "lambda = " <<  lambda <<  std::endl;

/*
 * Calcular x3 e y3
 * x3 = λ^2 − x1 − x2
 * y3 = λ(x1 − x3) − y1
 */
  x3 = pow(lambda, 2);
  x3 = x3 - x1 - x2;
  if(x3 < 0) {
    x3 = abs(x3) % _p;
    x3 = (-x3) + _p;
  }else{
    x3 = x3 % _p;
  }

  y3 = lambda * (x1 - x3) - y1;
  if(y3 < 0) {
    y3 = abs(y3) % _p;
    y3 = (-y3) + _p;
  }else{
    y3 = y3 % _p;
  }
}


/**
 * Calcular el valor de euclide solo en el caso de que lamda es una fraccion
*/
inline int Eliptica::valueEucler(int denominator) {
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
        return xLast;
}