#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"
#include "time.h"
#include <omp.h>
#define SIZE_DATA (1024*1024*64*2)

static double MEN_CHUNK[SIZE_DATA];


//Nueva versión del  algoritmo
int j, i, k, N, NUM_T;


int main(int argc, char **argv){

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
  for (i=0; i<N; i++){
     for(j=0; j<N; j++){
        double *pA, *pB, c0=0.0, c1=0.0, c2=0.0, c3=0.0;
	    pA = matrizA + (i*N);
        pB = matrizB + (j*N);
        k = N;
        while (k&3) // En caso de que N no sea multiplo de 4
        {
            c0 += (*pA * *pB);
            k--;
            pA++;
            pB++;
        }
        for (;k>0;k-=4, pA+=4, pB+=4) //Atacar cuatro elementos a la vez
        {
         c0 += (*pA * *pB);
         c1 += (*(pA+1) * *(pB+1));
         c2 += (*(pA+2) * *(pB+2));
         c3 += (*(pA+3) * *(pB+3));
        
        }
        matrizC[i*N+j] = c0+c1+c2+c3;

     }
  }
/**
    printf("Impresion Matriz C \n");
    printMatrix(N, matrizC);
**/
    sampleStop();

    printTime();



}
   
    return 0;
}
