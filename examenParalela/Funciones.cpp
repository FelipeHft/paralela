/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

    return resultado;
}