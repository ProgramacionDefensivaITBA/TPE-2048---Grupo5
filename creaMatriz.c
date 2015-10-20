#include <stdio.h>
#include "getnum.h"
#include <math.h>

int creaMatriz(int dif);

int
main()
{
int dificultad=0;
do {
    dificultad=getint("Ingrese la dificultad que desea, facil1, intermedio2 o dificil3:  ");
    if(dificultad != 1 && dificultad != 2 && dificultad != 3)
        printf("\nError\n");
} while(dificultad != 1 && dificultad != 2 && dificultad != 3);
if(creaMatriz(dificultad)) {
    printf("A jugar!\n");
    if(dificultad==3)
       printf("\nAnd may the odds be ever in your favor...\n\n");
}
else {
    printf("No tiene suficiente espacio para jugar este asombroso juego!\n");
    // LLAMADA A FUNCION QUIT?
}
return 0;
}


int
creaMatriz(int dificultad)
{
int **matriz;
int i, j, tamMat;

switch(dificultad) {
    case 1: {
        tamMat=64;
        break;
    }
    case 2: {
        tamMat=36;
        break;
    }
    case 3: {
        tamMat=16;
        break;
    }
}

matriz=calloc(tamMat, sizeof(int));

if(matriz == NULL)
    return 0;
else
    return 1;
}
