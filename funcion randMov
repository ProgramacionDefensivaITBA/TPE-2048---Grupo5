/*Agrega dos numeros iniciales, 11% de 4 y 89% de 2
Se agrega un numero, 2 o 4 luego de una jugada !=NULA */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int
main(void)
{
srand(time(NULL));                                          // No se donde meter el srand pero ahi funca.
printf("calcAzar = %d\n", calcAzar());
return 0;
}

int
calcAzar(void)
{
double azar;
azar = rand()/(double)RAND_MAX*(100-1)+1;                   // Tira un numero random entre 1 y 100
if(azar<11)                                                 // Asi calcula si devolverle un 2 o el raro caso del 4
    return 4;
else
    return 2;
}
