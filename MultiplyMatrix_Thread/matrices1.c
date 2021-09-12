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
#include <pthread.h>
// **argv: doble puntero
#define SIZE_DATA (1024*1024*64*3)

static double MEN_CHUNK[SIZE_DATA];
// Estrategia declaraciòn de todas las variables de forma global
int N;
int NUM_T;
double *matrizA, *matrizB, *matrizC;

void *multiply(void *arg){

    int i, j, k; // Contadores
    int ID_TH; // Identificador del threads
    int porcion; // Porciòn de la matriz C a enviar
    int inicioFila, finFila; // Inicio y fin de la porciòn de la matriz A

    ID_TH = *((int *) (arg)); // Se obtiene el identificador del hilo secuencialmente
    porcion = N/NUM_T; // Porcion a computar o calcular

    inicioFila = ID_TH * porcion; //
    finFila = (ID_TH + 1)*porcion; 

    for (i = inicioFila; i < finFila; i++){
        for (j = 0; j < N; j++){
            double *pA, *pB, suma=0.0;
    	    pA = matrizA + i*N;
	        pB = matrizB + j;
            for (k = 0; k < N; k++, pA++, pB+=N){
                 suma += (*pA * *pB);
            }
	    matrizC[i*N + j] = suma;
        }
    }
    return 0;
}

int main(int argc, char **argv){
    int COUNT_TH; // contador general de hilos
    pthread_t * hilos; // Declarando apuntadores a hilo POSIX
    
    N = (int) atof(argv[1]);
    NUM_T = (int) atof(argv[2]);

    matrizA = MEN_CHUNK;
    matrizB = matrizA + N*N;
    matrizC = matrizB + N*N;

    //printf("Inicializando matrices . . . \n");
    matrixInit(N, matrizA, matrizB, matrizC);

   sampleStart();
   //printf("Matriz A \n");
   //printMatrix(N, matrizA);
   //printf("Matriz B \n");
   //printMatrix(N, matrizB);

   //Declaraciòn de hilos y asignaciòn de memorìa
   hilos  = (pthread_t *) malloc (NUM_T* sizeof(pthread_t)); //Reserva de memoria
   // Se reparte el trabajo invocando cada hilo
   for (COUNT_TH = 0; COUNT_TH < NUM_T; COUNT_TH++)
   {
       int *tID; // Puntero identificador del hilo

       tID = (int *) malloc (sizeof(int));
       *tID = COUNT_TH; // Se apunta al contador general de hilos
       pthread_create(&hilos[COUNT_TH], NULL, multiply, (void *) tID);

   }
   // Espera a que todos los hilos hayan terminado (sincronizaciòn)
   for (COUNT_TH = 0; COUNT_TH < NUM_T; COUNT_TH++)
   {
       pthread_join(hilos[COUNT_TH], NULL);
   }
   

   
   //printf("Matriz C \n");
   //printMatrix(N, matrizC);

   sampleStop();

   printTime();
    
    return 0;
}
