// Realizar un programa que realice las siguientes operaciones
//Suma de matrices
//Substracción de matrices
//Multiplicación de matrices
//Presentación de matrices
//Matriz transpuesta
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include "matrices.h"
#include "time.h"
#include <pthread.h>

#define N 
int NUM_T;

void multMatrix(void *arg);
int A[N][N];
int B[N][N];
int C[N][N];

// **argv: doble puntero
int main(int argc, char **argv){

    int N;
    pthread_t * hilos;
    int COUNT_TH; // contador general de hilos
    

    N = (int) atof(argv[1]);
    NUM_T = (int) atof(argv[2]);
	
    

   sampleStart();
   matrixInit(N, A);
   matrixInit(N, B);
   
   hilos  = (pthread_t *) malloc (NUM_T* sizeof(pthread_t)); //Reserva de memoria
   // Se reparte el trabajo invocando cada hilo
   for (COUNT_TH = 0; COUNT_TH < NUM_T; COUNT_TH++)
   {
       int *tID; // Puntero identificador del hilo

       tID = (int *) malloc (sizeof(int));
       *tID = COUNT_TH; // Se apunta al contador general de hilos
       pthread_create(&hilos[COUNT_TH], NULL, multMatrix, (void *) tID);

   }
   // Espera a que todos los hilos hayan terminado (sincronizaciòn)
   for (COUNT_TH = 0; COUNT_TH < NUM_T; COUNT_TH++)
   {
       pthread_join(hilos[COUNT_TH], NULL);
   }

    //printf("Impresion Matriz A \n");
    
    //printMatrix(N, A);
    //printf("Impresion Matriz B \n");
    //matrixInit(N, B);
    //printMatrix(N, B);
    //printf("Impresion Matriz C \n");
    //matrixInit(N, C);
    //printMatrix(N, C);

    

    //printf("********OPERACIONES********** \n");
    //printf("* Suma de matrices A y B \n");
    //addMatrix(N, A, B, C);

    //printf("* Resta de matrices A y B \n");
    //minusMatrix(N, A,B,C);

    //printf("* Multiplicacion de matrices A y B \n");
    //multMatrix(N,A,B,C);

    //printf("* Transposicion de matrices A \n");
    //transpoMatrix(N,A,B);

    sampleStop();

    printTime();
    
   // getch();
    return 0;
}


void multMatrix(void *arg){
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            C[i][j] = 0;
            for (int k = 0; k < N; k++){
                 C[i][j] += A[i][k] - B[k][j];
            }
        }

    //printMatrix(N, matrixC);
}
