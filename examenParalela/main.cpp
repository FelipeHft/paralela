#include <cstdlib>
#include <stdio.h>
#include </usr/include/mpi/mpi.h>
#include "Funciones.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //inicializando mpi
    MPI_Init(NULL, NULL);
    
    //obteniendo numero total de procesadores
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    //obteniendo 'rank' del procesador
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    //obteniendo nombre del procesador
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    int matriz[3][3] = {{8,1,6},{3,5,7},{4,9,2}};
    
    int res;
    res = cuadradoMagico(matriz);
    printf("valor %d\n", res);
    
    
    //imprimiendo mensajes
    printf("Hellow world from the processor %s, rank %d out of %d processors\n",
            processor_name, world_rank, world_size);
    
    MPI_Finalize();
    
}

