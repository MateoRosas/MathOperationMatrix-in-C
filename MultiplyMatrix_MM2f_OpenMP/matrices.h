#ifndef OPERACIONMATRIX_H_INCLUDE
#define OPERACIONMATRIX_H_INCLUDE

void matrixInit(int N , double *matrizA, double *matrizB, double *matrizC);
void printMatrix(int N, double *matriz);
void multMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]);
void transpoMatrix(int N, double *matrizA, double *matrizT);

#endif
