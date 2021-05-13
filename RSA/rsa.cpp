#include "rsa.hpp"

//Constructor
RSA::RSA(){}

//Destructor
RSA::~RSA(){}

//algoritmo principal
void RSA::algorithm() {
    
    /**
     * Pedir los datos necesarios:
     * @param testOrigin = texto original
     * @param p = valor p
     * @param q = valor q
     * @param d = clave secreta junto con valor n (d, n), n = p * q
    */
    std::string textOrigin;
    int p, q, d;
    
    std::cout << "Texto original:";
    getline(std::cin, textOrigin);

    std::cout << "p (un numero primo) = ";
    std::cin >> p;

    std::cout << "q (un numero primo) = ";
    std::cin >> q;
    
    std::cout << "d (primo con φ(n))  = ";
    std::cin >> d;
    std::cout << std::endl;


    //Comprobarse que p y q son primos
    if(isPrimer(p) && isPrimer(q)) {
        std::cout << p << " y " << q << " son numeros primos." << std::endl;
    }else if(isPrimer(p)) {
        std::cout << q << " no es un numero primo." << std::endl;
    }else if(isPrimer(q)) {
        std::cout << p << " no es un numero primo." << std::endl;
    }else{
        std::cout << p << " y " << q << " no son numeros primos" << std::endl;
    }


    //Comprobar que d es primo con eucleValue
    int eV = calculate_eulerValue(p, q);
    std::cout << "se comprueba que d es primo con φ(n) = " << eV << std::endl;


    //Calcular el valor de e
    _e = calculate_e(d);
    std::cout << "El valor de e = " << _e << std::endl;

    
    //Calcular n
    int n = p * q;
    std::cout << "El valor de n = " << n;


    //Se pasa cada bloque a decimal para poder cifrar, obteniendo 312, 341, 3, 221, 121, 382, 
    //Calcular el valor de caracter para cada bloques
    int j = 1;
    int w = 0;
    while(w == 0){
        int a1 = pow(N_ALFABETO, j-1);
        int a2 = pow(N_ALFABETO, j);
        if(a1 < n && n < a2) {
            w = 1;
        }else{
            j++;
        }
    }
    int caracters = j-1; 
    std::cout << ", se divede el texto en bloques de " << caracters << std::endl;

    blockValue(textOrigin, caracters);


    //Se calcula en decimal el texto cifrado -> c = m^e (mod n)
    std::cout << "El texto cifrado en decimal: ";
    for(int i = 0; i < _r.size(); i++) {
        _base = _r.at(i);
        _mod = n;
        _power = _e;
        int c = montgomery();
        _m.push_back(c);
    }
    //Mostrar resultadp
    for(auto c:_m) {
        std::cout << c << " ";
    }
    std::cout << std::endl;


    //El proceso de descifrar -> m = c^d (mod n)
    /*
    for(int i = 0; i < _m.size(); i++) {
        _base = _m.at(i);
        _mod = n;
        _power = d;
        int m = montgomery();
        _m.push_back(m);
    }*/

}

//Comprobar que es un numero primo
bool RSA::isPrimer(int a) {
	bool yes = true;
	if(a < 2) {
        yes = false;
    }
    for(int i=2; i*i<=a;i++) {
		if(a % i == 0) {
			yes = false;
			break;
		}	
	}
	return yes;
}

//Calcular el eulerValue φ(n)
int RSA::calculate_eulerValue(int p, int q){
    _eulerValue = ( p - 1 ) * ( q - 1 );

    return _eulerValue;
}

//Calcular el valor de e
int RSA::calculate_e(int d) {
    int e = 2;
    while( (e * d % _eulerValue) != 1){
        if(e > 1 && e < _eulerValue){
            e++;
        }else{
            break;
        }
    }

    return e;
}

//Dividor en bloque para cifrar
void RSA::blockValue(std::string textOrigin, int n) {
    
    int result;
    std::vector<int> numVec;

    //Eliminar todos los espacios del textOrigin
    std::string::iterator end_pos = std::remove(textOrigin.begin(), textOrigin.end(), ' ');
    textOrigin.erase(end_pos, textOrigin.end());
    
    //Añadir X en caso de que no llega al tamaño
    while(textOrigin.size() % n != 0){
        textOrigin.push_back('X');
    }

    //Transformar todos las letras a numero para calcular cada bloque
    for(int i = 0; i < textOrigin.size(); i++) {
        int x = 0;
        //A-Z
        if((int)textOrigin.at(i) > 64 && (int)textOrigin.at(i) < 91) {
            x = (int)textOrigin.at(i) - 65;
        //a-z
        }else if((int)textOrigin.at(i) > 96 && (int)textOrigin.at(i) < 123){
            x = (int)textOrigin.at(i) - 97;
        }
        numVec.push_back(x);
    }

    //Calcular cada bloque a decimal para poder cifrar
    //ABCD 0*26^3+1*26^2+2*26+3 (caso de bloques de 4 caracteres)
    for(int i = 0; i < numVec.size(); i+=n) {
        result = 0;
        int size = i + n;
        for(int j = i, k = n; j < size; j++, k--) {
            int temp = pow(N_ALFABETO, k-1);
            result += numVec.at(j) * temp;
        }
        _r.push_back(result);
    }

    //Imprimir resultados
    std::cout << "Pasa cada bloque a decimal para poder cifrar:";
    for(auto a:_r) {
        std::cout << a << ", ";
    }
    
    std::cout << std::endl;
}

// Calcular en decimal el texto cifrado
// Utilizando el algoritmo de montgomery
// https://en.wikipedia.org/wiki/Montgomery_modular_multiplication enlace relacionado
int RSA::montgomery() {
	int res = 1;
	while (_power) {
		if (_power & 1) res = (res * _base) % _mod;
		_power>>= 1;
		_base = (_base * _base) % _mod;
	}
	return res;
}