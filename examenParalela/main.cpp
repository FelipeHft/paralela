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
    int matriz[3][3]={ {0,0,0},  {0,0,0}, {0,0,0} };
    int resultado;
    int ierr;
    
    

    MPI_Init(&argc, &argv); //inicializando mpi
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  //obteniendo numero total de procesadores
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  //obteniendo 'rank' del procesador
            
    
    if(opcion == "-f"){
        ifstream archivo_entrada;
        ofstream archivo_salida;
        archivo_entrada.open(rutaEntrada, ios::in);
        archivo_salida.open(rutaSalida, ios::out);
        if(archivo_entrada.fail() && archivo_salida.fail()){
            cout<<"Error al abrir el archivo!"<<endl;
            exit(1);
        }
        else{            
            while(!archivo_entrada.eof()){ //recorre archivo txt
                if(world_rank == 0){
                    getline(archivo_entrada, linea); //guardando linea del txt
                    
                    cout<<"esta es la linea: "<<linea<<endl;
                    if(linea.length() < 15){
                        cout<<"saliendo del while para leer"<<endl;
                        break;
                    }
                    else{
                        strcpy(lineaAux, linea.c_str()); //pasando de string a char
                        MPI_Send(&lineaAux, strlen(lineaAux)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
                        cout<<linea<<" enviado desde 0"<<endl;
                        MPI_Recv(&resultado, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &estado);
                        cout<<resultado<<" recibida por 0"<<endl;
                        if(resultado == 1){
                            linea = lineaAux; //pasando de char a string
                            archivo_salida << linea<<"\n";                        
                        }
                    }                                            
                    /*dest++; //cambia el procesador de destino
                    if(dest == 4){
                        dest = 1;
                    } */              
                }
                if(world_rank != 0){
                    cout<<"what: "<<linea<<endl;
                    if(linea.length() < 15){
                        cout<<"chao nos vimos"<<endl;
                        break;
                    }
                    MPI_Recv(&lineaAux, 40, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &estado);                                    
                    linea = lineaAux; //pasando de char a string
                    cout<< world_rank <<" a recibido: "<<lineaAux<<" y su largo es: "<<linea.length()<<endl;
                    transformarMatriz(linea, matriz);
                    resultado = cuadradoMagico(matriz);                
                    MPI_Send(&resultado, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);                      
                }                
            }
            ierr = MPI_Finalize();
            cout<<"ierr: "<<ierr<<endl;
            cout<<"estoy afuera del while fin"<<endl;
            
            archivo_entrada.close();
            archivo_salida.close();
            
                       
        }
        cout<<"cerrando arch"<<endl;
        
    }
    else{
        cout<<"Opción no válida"<<endl;
    }
    
    ierr = MPI_Finalize();
    cout<<"ierr: "<<ierr<<endl;
    
    return EXIT_SUCCESS;
    
}
