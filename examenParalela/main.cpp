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
    int dest=1;
    int tag = 0;
    int fin=0;
    string linea; 
    char lineaAux[40];
    char lineaEnvio[40] = "";
    MPI_Status estado;
    string opcion = argv[1];
    string rutaEntrada = argv[2];
    string rutaSalida = argv[4];
    int matriz[3][3], resultado;

    
    if(opcion == "-f"){
        ifstream archivo_entrada;
        ofstream archivo_salida;
        archivo_entrada.open(rutaEntrada, ios::in);
        archivo_salida.open(rutaSalida, ios::out);
        if(archivo_entrada.fail() && archivo_salida.fail()){
            cout<<"Error al abrir el archivo!"<<endl;
        }
        else{
            MPI_Init(NULL, NULL); //inicializando mpi
            MPI_Comm_size(MPI_COMM_WORLD, &world_size);  //obteniendo numero total de procesadores
            MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  //obteniendo 'rank' del procesador
            while(fin == 0){
                if(world_rank == 0){
                    while(!archivo_entrada.eof()){  //recorre archivo txt 
                        if(archivo_entrada.eof()){
                            fin = 1;
                            break;
                        }
                        
                        getline(archivo_entrada, linea); //guardando linea del txt
                        if(linea == ""){
                            fin = 1;
                            break;
                        }
                        else{
                            strcpy(lineaAux, linea.c_str()); //pasando de string a char                    
                            MPI_Send(&lineaAux, strlen(lineaAux)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
                            cout<<lineaAux<<" enviado desde 0"<<endl;
                            MPI_Recv(&lineaEnvio, 40, MPI_CHAR, dest, 1, MPI_COMM_WORLD, &estado);
                            if(lineaEnvio[0] != 'x'){
                                linea = lineaAux; //pasando de char a string
                                archivo_salida << linea<<"\n";                        
                            }                    
                            dest++; //cambia el procesador de destino
                            if(dest == 4){
                                dest = 1;
                            }
                        }                                           
                    }                
                }
                if(fin == 1) break;
                else{
                   MPI_Recv(&lineaAux, 40, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &estado);
                    cout<< world_rank <<" a recibido: "<<lineaAux<<endl;
                    linea = lineaAux; //pasando de char a string
                    transformarMatriz(linea, matriz);
                    resultado = cuadradoMagico(matriz);                
                    if(resultado == 0){
                        strcpy(lineaEnvio, linea.c_str());
                        MPI_Send(&lineaEnvio, strlen(lineaAux)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);                
                        //cout<<world_rank<<" a enviado: "<<lineaEnvio<<endl;
                        //archivo_salida << linea<<"\n";
                    }
                    else{
                        lineaEnvio[0] = 'x';
                        MPI_Send(&lineaEnvio, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
                        //cout<<world_rank<<" a enviado: "<<lineaEnvio<<endl;     
                    } 
                }                
            }
             MPI_Finalize();           
        }
        archivo_entrada.close();
        archivo_salida.close();
    }
    else{
        cout<<"Opción no válida"<<endl;
    }
    
    
}
