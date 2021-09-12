#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>

void matrixInit(int N ,int matrixA[N][N]){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           matrixA[i][j] = 2*(j-i);
        }
        
    }
    

}

void printMatrix(int N, int matrixA[N][N]){
    for (int i = 0; i < N; i++){
        
        for (int j = 0; j < N; j++){
            printf("%d ",matrixA[i][j]);
        }
        printf("\n");
    }



}

void addMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        
    }
   // printMatrix(N, matrixC);

}

void minusMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    //printMatrix(N, matrixC);
}

void multMatrix(void *arg){
    int N = 50;
    int A[N][N];
    int B[N][N];
    int C[N][N];
    matrixInit(N, A);
    matrixInit(N, B);
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            C[i][j] = 0;
            for (int k = 0; k < N; k++){
                 C[i][j] += A[i][k] - B[k][j];
            }
        }

    //printMatrix(N, matrixC);
}

void transpoMatrix(int N, int matrixA[N][N], int matrixT[N][N]){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrixA[i][j] =  matrixT[j][i];


 //   printMatrix(N, matrixA);
}
