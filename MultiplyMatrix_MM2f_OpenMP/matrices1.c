#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"
#include "time.h"
#include <omp.h>
#define SIZE_DATA (1024*1024*64*2)

static double MEN_CHUNK[SIZE_DATA];


//Nueva versión del  algoritmo


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

int i, j, k;
    
omp_set_num_threads(NUM_T);


    sampleStart();

#pragma omp parallel for
  for (i=0; i<N; i+=2){
     for(j=0; j<N; j+=2){
        double *pA, *pB, c0=0.0, c1=0.0, c2=0.0, c3=0.0;
	pA = matrizA + (i*N);
        pB = matrizB + (j*N);
        for(k=N; k>0; k-=2, pA+=2, pB+=2){
	  double a0, a1, a2, a3;
	  double b0, b1, b2, b3;
	  a0 = *pA;
	  a1 = *(pA + 1);
	  a2 = *(pA + 2);
	  a3 = *(pA + 3);

	  b0 = *pB;
	  b1 = *(pB + 1);
	  b2 = *(pB + 2);
	  b3 = *(pB + 3);
		
	  c0 += a0*b0 + a1*b1;
	  c1 += a0*b2 + a1*b3;
          c2 += a2*b0 + a3*b1;
	  c3 += a2*b2 + a3*b3;
         }
     pB = matrizC + i*N+j;
     *(pB + 1) = c1;
     *(pB + 2) = c2;
     *(pB + 3) = c3;
     }
  }

 //   printf("Impresion Matriz C \n");
 //   printMatrix(N, matrizC);

    sampleStop();

    printTime();



}
   
    return 0;
}
