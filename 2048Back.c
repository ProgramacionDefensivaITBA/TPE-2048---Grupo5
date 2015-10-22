#include <stdio.h>
#include "getnum.h"
#include <stdlib.h>
#include "backend2048.h"


int
tamMatriz(int dificultad)
{
int tamMat;

switch(dificultad) {
    case 1: {
        tamMat=8;
        break;
    }
    case 2: {
        tamMat=6;
        break;
    }
    case 3: {
        tamMat=4;
        break;
    }
}
return tamMat;
}
/*
int **creaMatriz(int dim)                       // faltan cosas
{
int **matriz;
int *aux;
int i, flagEspacio=0;

matriz=calloc(dim, sizeof(*matriz));

if(matriz==NULL) {
    free(matriz);
    return NULL;
} else {
    for(i=0; i<dim && flagEspacio==0; i++) {
        aux=calloc(dim, sizeof(matriz));

        if(aux==NULL) {
            flagEspacio=1;
        } else {
            matriz[i]=aux;
        }
    }
    if(flagEspacio) {
        liberaMatriz(i, matriz);
        return NULL;
    } else {
        return matriz;
    }
}
}

void liberaMatriz(int n, int **matriz)
{
int i;
for(i=0; i<n; i++)
    free(matriz[i]);
free(matriz);
}
*/
double randNormalize(void)
{
    return rand()/((double)RAND_MAX+1);
}

int randInt(int izq, int der)
{
    return (int)(randNormalize()*(der-izq+1)+izq);
}

int calcAzar(void)
{
double azar;
azar = rand()/(double)RAND_MAX*(100-1)+1;
/* porcentaje de probabilidad de que salga un 4 es 11% */
if(azar<12)
    return 4;
else
    return 2;
}

void nuevoNum(int dim, int **matriz)
{
    int i, j;

    do{
            i=randInt(0, dim-1);
            j=randInt(0, dim-1);

    }while(matriz[i][j]!=0);

    matriz[i][j]=calcAzar();
}

