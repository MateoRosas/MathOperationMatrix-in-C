// Realizar un programa que realice las siguientes operaciones
//Suma de matrices
//Substracción de matrices
//Multiplicación de matrices
//Presentación de matrices
//Matriz transpuesta
#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"
#include "time.h"
//#include <pthread.h>
#include <omp.h>
// **argv: doble puntero
#define SIZE_DATA (1024*1024*64*3)

static double MEN_CHUNK[SIZE_DATA];
// Estrategia declaraciòn de todas las variables de forma global


int main(int argc, char **argv){

    int N;
    int NUM_T;

    //int COUNT_TH; // contador general de hilos
    //pthread_t * hilos; // Declarando apuntadores a hilo POSIX
    
    N = (int) atof(argv[1]);//Tamaño de la matriz
    NUM_T = (int) atof(argv[2]); // Cantidad de hilos a emplear

//#pragma omp parallel
{

    double *matrizA, *matrizB, *matrizC;
    matrizA = MEN_CHUNK;
    matrizB = matrizA + N*N;
    matrizC = matrizB + N*N;
    
    //Se deja que el hilo principal (master) haga las rutinas de inicialización
//#pragma omp master

    //printf("Inicializando matrices . . . \n");
    matrixInit(N, matrizA, matrizB, matrizC);

    omp_set_num_threads(NUM_T);

    sampleStart();
   //Prueba de multiplicación de matrices con OpenMP
#pragma omp parallel for
   for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            double *pA, *pB, suma=0.0;
	        pA = matrizA + i*N;
	        pB = matrizB + j;
            for (int k = 0; k < N; k++, pA++, pB+=N){
                 suma += (*pA * *pB);
            }
	    matrizC[i*N + j] = suma;
        }
    }

    sampleStop();
}
  

   printTime();
    
    return 0;
}
