# MathOperationMatrix in C

Each directory contains a main program developed in C, which uses a .h interface where the matrix multiplication methods and matrix initialization are located. We also use a time interface which will allow us to perform the runtime capture where the matrix multiplication method is performed. To be more efficient in the execution of each code in C, we use a Makefile, therefore to compile all the code we write the following: make clean; make matrices1.

There is another file (.pl) that allows the execution of N times of the program, this in order to calculate the multiplication of matrices in a certain size N_t and also in a certain number of threads N_h. 

The version of each matrix multiplication is shown below:

MultiplyMatrix_Array: This is based on the multiplication of matrices that we commonly perform, without taking into account the memory space we use for the result of the multiplication. As a result, when multiplying matrices with a number greater than 800, there is a segmentation fault (core dumb), which indicates that it accesses memory that does not belong to the program.

```
void multMatrix(int N, int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            matrixC[i][j] = 0;
            for (int k = 0; k < N; k++){
                 matrixC[i][j] += matrixA[i][k] - matrixB[k][j];
            }
        }
}


```

MultiplyMatrix_Pointers: This is based on matrix multiplication where the memory location to be occupied is referenced by pointers, the program reserves a memory space and the multiplication is analyzed in the form of two vectors that are traversed by pointers that jump between the number of rows and columns to perform the multiplication.

```
void multMatrix(int N, double *matrizA, double *matrizB, double *matrizC){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                double *pA, *pB, suma=0.0;
    	        pA = matrizA + i*N;
    	        pB = matrizB + j;
                for (int k = 0; k < N; k++, pA++, pB+=N){
                     suma += (*pA * *pB);
                }
    	    matrizC[i*N + j] = suma;
            }
        }
    }

```


MultiplyMatrix_Thread: It is based on the division of work by logical processing units (CPUs). It uses the POSIX Threads library to split workflows within the code. The function halves the vectors it is multiplying and calls two CPUs to each perform one half of the work. This reduces the execution time.

```
void *multiply(void *arg){
    
        int i, j, k;
        int ID_TH;
        int porcion; 
        int inicioFila, finFila;
    
        ID_TH = *((int *) (arg));
        porcion = N/NUM_T;
    
        inicioFila = ID_TH * porcion; 
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

```
