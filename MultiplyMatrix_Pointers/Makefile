GCC = gcc
FLAGS = -ansi -pedantic -Wall -std=c99
C_FLAGS = -lm
PROGRAMAS = matrices1

matrices1:
	$(GCC) $(FLAGS) operacionmatrix.c -c
	$(GCC) $(FLAGS) time.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) -o $@ $@.o operacionmatrix.o time.o

clean:
	$(RM) $(PROGRAMAS) *.o
