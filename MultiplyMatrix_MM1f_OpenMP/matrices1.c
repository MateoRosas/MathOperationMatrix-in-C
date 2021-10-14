#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"
#include "time.h"
#include <omp.h>
#define SIZE_DATA (1024*1024*64*2)

static double MEN_CHUNK[SIZE_DATA];

int main(int argc, char **argv){

    int N;
    int NUM_T;

    N = (int) atof(argv[1]);
    NUM_T = (int) atof(argv[2]);

{

double *matrizA, *matrizB, *matrizC;
matrizA = MEN_CHUNK;
matrizB = matrizA + N*N;
matrizC = matrizB + N*N;


matrixInit(N, matrizA, matrizB, matrizC);
/**
    printf("Impresion Matriz A \n");
    printMatrix(N, matrizA);
    printf("Impresion Matriz B \n");
    printMatrix(N, matrizB);

printf("Impresión Matriz Transpuesta \n");
transpoMatrix(N,matrizB, matrizB);
printMatrix(N, matrizB);
**/


    
omp_set_num_threads(NUM_T);


    sampleStart();

#pragma omp parallel for
  for (int i=0; i<N; i++){
     for(int j=0; j<N; j++){
        double *pA, *pB, suma=0.0;
        pA = matrizA + (i*N);
        pB = matrizB + (j*N);
        for(int k=0; k<N; k++, pA++, pB++){
          suma += (*pA * *pB);
         }
     matrizC[i*N + j] = suma;
     }
  }

 //   printf("Impresion Matriz C \n");
 //   printMatrix(N, matrizC);

    sampleStop();

    printTime();



}
   
    return 0;
}
