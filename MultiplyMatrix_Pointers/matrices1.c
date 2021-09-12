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
// **argv: doble puntero
#define SIZE_DATA (1024*1024*64)

static double MEN_CHUNK[SIZE_DATA];

int main(int argc, char **argv){

    int N;
    N = (int) atof(argv[1]);
    double *matrizA;
    double *matrizB;
    double *matrizC;

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
 
   multMatrix(N,matrizA,matrizB,matrizC);
   //printf("Matriz C \n");
   //printMatrix(N, matrizC);

   sampleStop();

   printTime();
    
    return 0;
}
