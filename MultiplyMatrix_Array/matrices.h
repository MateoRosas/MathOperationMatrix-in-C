#ifndef OPERACIONMATRIX_H_INCLUDE
#define OPERACIONMATRIX_H_INCLUDE

void matrixInit(int N ,int matrixA[N][N]);
void printMatrix(int N, int matrixA[N][N]);
void addMatrix(int N, int matrixA[N][N],int matrixB[N][N],int matrixC[N][N]);
void minusMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]);
void multMatrix(void *arg);
void transpoMatrix(int N, int matrixA[N][N], int matrixT[N][N]);

#endif
