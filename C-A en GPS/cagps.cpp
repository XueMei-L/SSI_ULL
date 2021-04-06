#include "cagps.h"

/* Constructor */
CAGPS::CAGPS()
{
    int_Vec(Vec_G1);
    int_Vec(Vec_G2);
}


/* Destructor */
CAGPS::~CAGPS(){}


/* Iniciar los dos vectores a 1 */
void CAGPS::int_Vec(std::vector<int>& vec)
{
    for(int i = 0; i < 10; i++)
    {
        vec.push_back(1);
    }
}

/* Mostrar vector */
void CAGPS::ShowVec(const std::vector<int>& vec)
{
    for(auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        std::cout << *iter << " "; 
    }
}

/* algoritmo para realizar la realimentacion y cambio */
void CAGPS::algoritmo(int veces)
{
    int vez = 1;

    int insertNumbG1;
    int insertNumbG2;

    std::vector<int> result_G1;     //la ultima posicion de G1
    std::vector<int> result_G2;     //la suma de la ID1

    while(vez <= veces){

        int countG1 = 0;
        int countG2 = 0;
        int countR2 = 0;

        countG1 += (Vec_G1[2] + Vec_G1[9]);
        countG2 += (Vec_G2[1] + Vec_G2[2] + Vec_G2[5] + Vec_G2[7] + Vec_G2[8] + Vec_G2[9]);
        countR2 += (Vec_G2[1] + Vec_G2[5]);
        
        if(countG1 % 2 == 0){
            insertNumbG1 = 0;
        }else {
            insertNumbG1 = 1;
        }

        if(countG2 % 2 == 0){
            insertNumbG2 = 0;
        }else {
                insertNumbG2 = 1;
            }  
         
        result_G1.push_back(Vec_G1[9]);
        result_G2.push_back(countR2);

        std::cout << std::endl << "G1:";
        deleteLastNumber(Vec_G1, insertNumbG1);
            
        std::cout << " ----- G2:";
        deleteLastNumber(Vec_G2, insertNumbG2);
    vez++;
    }

    std::cout << std::endl << std::endl << "La secuencia de C/A RPN1:";
    F_Xor(result_G1, result_G2);
}


void CAGPS::deleteLastNumber(std::vector<int>& vec, int number){
    
    ShowVec(vec);
    std::cout << " Realimentacion:" << number;
    
    //eliminar el ultimo numero
    vec.pop_back();
    //anadie en la posicion 0 el valor de realimentacion
    vec.insert(vec.begin(), number);
}


void CAGPS::F_Xor(std::vector<int>& G1, std::vector<int>& G2)
{
    std::vector<int> final_result;
    for(int i = 0; i < G1.size(); i++){
        if((G1.at(i) + G2.at(i)) % 2 == 0)
        {
            final_result.push_back(0);
        }else {
            final_result.push_back(1);
        }
    }
    ShowVec(final_result);
    std::cout << std::endl;
}