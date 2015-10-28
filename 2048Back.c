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

int **creaMatriz(int dim)                       // faltan cosas
{
int **matriz;
int *aux;
int i, noHayEspacio=0;

matriz=calloc(dim, sizeof(*matriz));
if(matriz==NULL) {
    free(matriz);
    return NULL;
} else {
    for(i=0; i<dim && noHayEspacio==0; i++) {
        aux=calloc(dim, sizeof(matriz));

        if(aux==NULL) {
            noHayEspacio=1;
        } else {
            matriz[i]=aux;
        }
    }
    if(noHayEspacio) {
        liberaMatriz(i, matriz);
        return NULL;
    } else {
        return matriz;
    }
}
}

void siCoincideD(int i, int j, int ** matriz)
{
int k;
for(k=j-1; k>=0; k--) {
    if(matriz[i][j]==matriz[i][k]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[i][k] = 0;
        return;
    }
    if(matriz[i][k] != 0 && matriz[i][k] != matriz[i][j])
        return;
}
}

void siCoincideA(int i, int j, int ** matriz, int dim)
{
int k;
for(k=j+1; k<dim; k++) {
    if(matriz[i][k]==matriz[i][j]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[i][k] = 0;
        return;
    }
    if(matriz[i][k] != 0 && matriz[i][k] != matriz[i][j])
        return;
}
}

void siCoincideW(int i, int j, int ** matriz, int dim)
{
int k;
for(k=i+1; k<dim; k++) {
    if(matriz[k][j]==matriz[i][j]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[k][j] = 0;
        return;
    }
    if(matriz[k][j] != 0 && matriz[k][j] != matriz[i][j])
        return;
}
}

void siCoincideS(int i, int j, int ** matriz)
{
int k;
for(k=i-1; k>=0; k--) {
    if(matriz[k][j]==matriz[i][j]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[k][j] = 0;
        return;
    }
    if(matriz[k][j] != 0 && matriz[k][j] != matriz[i][j])
        return;
}
}

void movimiento(char * c, int dim, int ** matriz)
{
int i, j, k, l;
/*
de atras para adelante... { if( ! 0 ) then { if(match) { num*2 ; "free"(elDeSobra)... rellenar con ceros ; } } }
*/
switch(*c) {
    case 'd': {
        for(i=0; i<dim; i++)
            for(j=dim-1; j>=0; j--) {
                if(matriz[i][j] != 0) {
                    siCoincideD(i, j, matriz);
                    if(j!=dim-1) {
                        l=j;
                        for(k=j+1; k<dim && l<dim-1; k++, l++)
                            if(matriz[i][k]==0) {
                                matriz[i][k]=matriz[i][l];
                                matriz[i][l]=0;
                            }
                    }
                }
            }
            break;
}
    case 'a': {
            for(i=0; i<dim; i++)
                for(j=0; j<dim; j++) {
                    if(matriz[i][j] != 0) {
                        siCoincideA(i, j, matriz, dim);
                        if(j!=0) {
                            l=j;
                            for(k=j-1; k>=0 && l>0; k--, l--)
                                if(matriz[i][k]==0) {
                                    matriz[i][k]=matriz[i][l];
                                    matriz[i][l]=0;
                                }
                        }
                    }
                }
                break;
    }
    case 'w': {
                for(j=0; j<dim; j++)
                    for(i=0; i<dim; i++) {
                        if(matriz[i][j] != 0) {
                            siCoincideW(i, j, matriz, dim);
                            if(i!=0) {
                                l=i;
                                for(k=i-1; k>=0 && l>0; k--, l--)
                                    if(matriz[k][j]==0) {
                                        matriz[k][j]=matriz[l][j];
                                        matriz[l][j]=0;
                                    }
                            }
                        }
                    }
                    break;
    }
    case 's': {
        for(j=0; j<dim; j++)
            for(i=dim-1; i>=0; i--) {
                if(matriz[i][j] != 0) {
                    siCoincideS(i, j, matriz);
                    if(i!=dim-1) {
                        l=i;
                        for(k=i+1; k<dim && l<dim-1; k++, l++)
                            if(matriz[k][j]==0) {
                                matriz[k][j]=matriz[l][j];
                                matriz[l][j]=0;
                            }
                    }
                }
            }
            break;
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

int nuevoNum(int dim, int **matriz)
{
    int i, j, hayCeros=0;

    for(i=0; i<dim && hayCeros==0; i++)
        for(j=0; j<dim && hayCeros==0; j++)
            if(matriz[i][j]==0)
                hayCeros=1;

    if(hayCeros==1){
        do{
            i=randInt(0, dim-1);
            j=randInt(0, dim-1);

        } while(matriz[i][j]!=0);
        matriz[i][j]=calcAzar();
    }
return hayCeros;
}
/*
int verifMats(int dim, int ** matAux, int ** matAct)
{
int i, j, distintas=0;

for(i=0; i<dim && distintas==0; i++)
    for(j=0; j<dim && distintas==0; j++)
        if(matAct[i][j] != matAux[i][j])
            distintas=1;

return distintas;
}
*/
int cantUndo(int dificultad)
{
int undo;

switch(dificultad) {

    case 1: {
              undo=8;
              break;
    }
    case 2: {
              undo=4;
              break;
    }
    case 3: {
              undo=2;
              break;
    }
}
return undo;
}

