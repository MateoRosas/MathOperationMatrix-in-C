# MathOperationMatrix in C

Each directory contains a main program developed in C, which uses a .h interface where the matrix multiplication methods and matrix initialization are located. We also use a time interface which will allow us to perform the runtime capture where the matrix multiplication method is performed. To be more efficient in the execution of each code in C, we use a Makefile, therefore to compile all the code we write the following: make clean; make matrices1.

There is another file (.pl) that allows the execution of N times of the program, this in order to calculate the multiplication of matrices in a certain size N_t and also in a certain number of threads N_h. 

The version of each matrix multiplication is shown below:

**MultiplyMatrix_Array**: This is based on the multiplication of matrices that we commonly perform, without taking into account the memory space we use for the result of the multiplication. As a result, when multiplying matrices with a number greater than 800, there is a segmentation fault (core dumb), which indicates that it accesses memory that does not belong to the program.

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

**MultiplyMatrix_Pointers**: This is based on matrix multiplication where the memory location to be occupied is referenced by pointers, the program reserves a memory space and the multiplication is analyzed in the form of two vectors that are traversed by pointers that jump between the number of rows and columns to perform the multiplication.

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


**MultiplyMatrix_Thread**: It is based on the division of work by logical processing units (CPUs). It uses the POSIX Threads library to split workflows within the code. The function halves the vectors it is multiplying and calls two CPUs to each perform one half of the work. This reduces the execution time.

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

**MultiplyMatrix_MM1c_OpenMP**: It is based on the latest code containing the POSIX Threads library but with changes. This version uses the OpenMP library so that at the hardware level the machine can communicate with the computation cores and redistribute the workflows between them and this produces a better level of parallel instruction:

```
#pragma omp parallel for
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

```

**MultiplyMatrix_MM1f_OpenMP**: 
```
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
```

**MultiplyMatrix_MM1fu_OpenMP**: 
```

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
```

**MultiplyMatrix_MM2f_OpenMP**: 
```
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

```



To compile each folder run the following commands in the terminal at the folder address:

```
    $ make clean; make matrices1
    $ ./matrices1 [size of matrix] [number of threads]
```
If you want to compile more than thirty times at one execution, you need to open the 'lanzador.pl' file and verify the code at the first lines where it's explicit the size of matrix and the number of threads which you can change. After the respective configuration run the following command:

```
    $ ./lanzador.pl
```
