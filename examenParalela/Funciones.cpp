#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;

int cuadradoMagico(int matriz[][3]){
    int constanteM = 0;
    int aux;
    int resultado = 0; //1 no es cuadrado magico; 0 es cuadrado magico
    

    for(int i=0; i<3; i++){ //revisando filas
        aux = 0;
        for(int j=0; j<3; j++){
            aux += matriz[i][j];
        }
        if(constanteM == 0){ //crea la constante magica si aun no ha sido asignada
            constanteM = aux;
        }
        else{
            if(aux != constanteM){  //si la suma de la fila no es la misma
                resultado = 1;      //que la constante magica, no es un cuadrado 
                break;              //magico por lo que resultado=1
            }
        }    
    }
        
      
    for(int i=0; i<3; i++){ //revisando columnas
        aux = 0;
        for(int j=0; j<3; j++){
            aux += matriz[j][i];
        }
        if(aux != constanteM){
            resultado = 1;
            break;
        }
    }
       
      
    aux = 0;
    for(int i=0; i<3; i++){ //revisando diagonal(izquierda derecha)
        for(int j=0; j<3; j++){
            if(i == j){
                aux += matriz[i][j];
            }
        }
    }
    if(aux != constanteM){
        resultado = 1;
    }
        
    aux = 0;
    for(int i=0; i<3; i++){ //revisando diagonal (derecha izquierda)
        for(int j=0; j<3; j++){
            if(i==0 && j==2){
                aux += matriz[i][j];
            }
            if(i==1 && j==1){
                aux += matriz[i][j];
            }
            if(i==2 && j==0){
                aux += matriz[i][j];
            }
        }
    }
    if(aux != constanteM){
        resultado = 1;
    }

    return resultado;   //devuelve si la matriz es un cuadrado magico o no
}

void transformarMatriz(string linea, int matriz[][3]){
    int largo = linea.length();
    int restaAux;
    int num, pos=1, contador=0;
    string numS;
    int arregloAux[9];
    for(int i=1; i<largo; i++){ //se recorre la linea
        //se toman las posiciones de ',' y ';' para separarlos de los numeros
        if(linea[i] == ',' || linea[i] == ';'){  
            if(contador == 0){
                restaAux = i-1;
                numS = linea.substr(1, restaAux);   
            }
            else{
                restaAux = i - pos - 1;
                numS = linea.substr(pos+1, restaAux);
            }
            pos = i;
            num = stoi(numS); //se transforma el numero de string a int
            arregloAux[contador] = num; //se agrega el num a un arreglo auxiliar
            contador++;
        }
        //se guarda el ultimo numero en el arreglo auxiliar
        if(linea[i] == ']'){ 
            restaAux = i - pos - 1;
            numS = linea.substr(pos+1, restaAux);
            num = stoi(numS);
            arregloAux[contador] = num;
        }
    }
    
    int posArreglo = 0;
    for(int i = 0; i<3; i++){ //convertir de arreglo a matriz
        for(int j = 0; j<3; j++){
            matriz[i][j] = arregloAux[posArreglo];
            posArreglo++;
        }
    }
    
    
}
