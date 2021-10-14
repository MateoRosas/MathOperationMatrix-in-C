#include <stdlib.h>
#include <stdio.h>

int main(){

int n[5];

printf("Llenado del vector \n");
for(int i=0; i<5;i++)
{
printf("Ingrese un Número [%d] \n", i);
scanf("%d", &n[i]);
printf("\n");
}

printf("Impresión del vector \n");
for(int i=0; i<5;i++)
{
printf("Vector [%i]: %d \n",i , n[i]);
}

//Es mucho más eficiente recorrer por punteros
//
printf("Impresión del vector por recorrido del puntero \n");
for(int i=0; i<6;i++)
{
printf("Puntero [%i]: %d \n",i, *(n+i));
}

return 0;
}
