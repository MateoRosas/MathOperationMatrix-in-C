# MathOperationMatrix in C


MultiplyMatrix_Array: This is based on the multiplication of matrices that we commonly perform, without taking into account the memory space we use for the result of the multiplication. As a result, when multiplying matrices with a number greater than 800, there is a segmentation fault (core dumb), which indicates that it accesses memory that does not belong to the program.


MultiplyMatrix_Pointers: This is based on matrix multiplication where the memory location to be occupied is referenced by pointers, the program reserves a memory space and the multiplication is analyzed in the form of two vectors that are traversed by pointers that jump between the number of rows and columns to perform the multiplication.


MultiplyMatrix_Thread: It is based on the division of work by logical processing units (CPUs). It uses the POSIX Threads library to split workflows within the code. The function halves the vectors it is multiplying and calls two CPUs to each perform one half of the work. This reduces the execution time.
