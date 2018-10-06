#include <cstdlib>
#include <stdio.h>
#include </usr/include/mpi/mpi.h>
#include "Funciones.h"
#include <fstream>
#include <valarray>
#include <string.h>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int world_size;
    int world_rank;
    //int dest=1;
    string linea; 
    char lineaAux[40];
    MPI_Status estado;
    string opcion = argv[1];
    string rutaEntrada = argv[2];
    string rutaSalida = argv[4];
    int matriz[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    int resultado;
    
    

    MPI_Init(&argc, &argv); //inicializando mpi
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  //obteniendo numero total de procesadores
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  //obteniendo 'rank' del procesador
            
    
    if(opcion == "-f"){
        ifstream archivo_entrada; 
        ofstream archivo_salida;
        archivo_entrada.open(rutaEntrada, ios::in); //abriendo archivo modo lectura
        archivo_salida.open(rutaSalida, ios::out);  //creando archivo para escritura
        if(archivo_entrada.fail() || archivo_salida.fail()){
            //si no se puede abrir el archivo o crear se termina el programa
            cout<<"Error con los archivos!"<<endl;
        }
        else{            
            while(!archivo_entrada.eof()){ //recorre archivo txt
                getline(archivo_entrada, linea); //guardando linea del txt en linea
                if(world_rank == 0){ //se toma el cpu 0
                    if(linea.length() < 15){
                        //al llegar al final del archivo se sale del ciclo
                        break;
                    }
                    else{
                        strcpy(lineaAux, linea.c_str()); //pasando de string a char
                        //envia la lineaAux al cpu 1
                        MPI_Send(&lineaAux, strlen(lineaAux)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
                        //recive desde el cpu 1 el valor de resultado
                        MPI_Recv(&resultado, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &estado);
                        if(resultado == 0){
                            //si es 0(es decir un cuadrado magico) se guarda en el archivo de salida
                            archivo_salida << linea<<"\n";                        
                        }
                    }                                            
                    /*dest++; //cambia el procesador de destino
                    if(dest == 4){
                        dest = 1;
                    } */             
                }
                else{ //empieza a funcionar cpu 1
                    if(linea.length() < 15){
                        break;
                    }
                    //recive desde el cpu 0 la linea aux 
                    MPI_Recv(&lineaAux, 40, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &estado);                                    
                    linea = lineaAux; //pasando de char a string
                    transformarMatriz(linea, matriz); //de la linea se crea la matriz
                    resultado = cuadradoMagico(matriz); //se verifica si es cuadrado magico
                    //envia el resultado al cpu 0
                    MPI_Send(&resultado, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);                      
                }                
            }
            //se cierran los archivos
            archivo_entrada.close();
            archivo_salida.close();            
        }
    }
    else{
        cout<<"Opción no válida"<<endl;
    }
    //fin mpi
    MPI_Finalize();
    
    
    return EXIT_SUCCESS;
    
}
