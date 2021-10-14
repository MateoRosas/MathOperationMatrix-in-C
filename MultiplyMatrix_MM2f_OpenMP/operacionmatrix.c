#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>

void matrixInit(int N , double *matrizA, double *matrizB, double *matrizC){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           matrizA[j+i*N] = 2.0*(j+i);
	   matrizB[j+i*N] = 3.2*(j+i);
	   matrizC[j+i*N] = 1.0;
        }
        
    }
    

}

void printMatrix(int N, double *matriz){
    for (int i = 0; i < N; i++){
        
        for (int j = 0; j < N; j++){
            printf("%f ",matriz[j+i*N]);
        }
        printf("\n");
    }



}

void multMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            matrixC[i][j] = 0;
            for (int k = 0; k < N; k++){
                 matrixC[i][j] += matrixA[i][k] - matrixB[k][j];
            }
        }

}

void transpoMatrix(int N, double *matrizA, double *matrizT){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrizA[j+i*N] =  matrizT[i+j*N];
}

