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

void siCoincide(int i, int j, int ** matriz)
{
int k;
for(k=j-1; k>0; k--) {
    if(matriz[i][j]==matriz[i][k]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[i][k] = 0;
        return;
    }
}
}

void movimiento(char * c, int dim, int ** matriz)
{
int i, j, k, l;
/*
de atras para adelante... { if( ! 0 ) then { if(match) { num*2 ; free(elDeSobra); rellenar con ceros? ; } } }
*/
switch(*c) {
    case 'd': {
        for(i=0; i<dim; i++)
            for(j=dim-1; j>=0; j--) {
                if(matriz[i][j] != 0) {
                    siCoincide(i, j, matriz);
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

void nuevoNum(int dim, int **matriz)
{
    int i, j;

    do{
            i=randInt(0, dim-1);
            j=randInt(0, dim-1);

    }while(matriz[i][j]!=0);

    matriz[i][j]=calcAzar();
}

int
leerEntrada(char nombreArchivo[36], char *dirVec)
{
enum estado {MOVIMIENTO=1, UNDO, SAVE, QUIT, ERROR};
char turno, c;
char * quit="uit\n";
char * save="ve ";
char * undo="ndo\n";
int i, j, estado=0;

turno=getchar();

	    switch(turno) {
			case 'w': {
			    if(getchar()=='\n') {
                    *dirVec=turno;
                    estado=MOVIMIENTO;
			    } else
                    estado=ERROR;
			    break;
			}
			case 'a': {
			    if(getchar()=='\n') {
                    *dirVec=turno;
                    estado=MOVIMIENTO;
			    } else
                    estado=ERROR;
			    break;
			}
			case 'd': {
			    if(getchar()=='\n') {
                    *dirVec=turno;
                    estado=MOVIMIENTO;
			    } else
                    estado=ERROR;
			    break;
			}
			case 'u': {
			    for(i=0; i<4 && getchar() == undo[i] ; i++)
               			;
                	    if(i==4)
		                    estado=UNDO;
			    else
		                    estado=ERROR;
                	break;
			}
			case 's': {
			    c=getchar();
			    if(c=='\n') {
                    *dirVec=turno;
                    estado=MOVIMIENTO;
			    } else if(c=='a') {
			        for(i=0; i<3 && getchar() == save[i] ; i++)
                        ;
                    if(i==3) {
                        estado=SAVE;
                        j=0;
                        do
                            nombreArchivo[j] = getchar();
                        while(j<35 && (nombreArchivo[j++]!='\n'));
                        nombreArchivo[j]='\0';
                        if(j==35)                                       // ESTE PRINTF NO VA ACA EN EL BACKEND!
                            printf("\nEl nombre del archivo guardo solo los primeros 35 chars!!\n");
                        } else
                            estado=ERROR;
                } else
                    estado=ERROR;
				break;
			}
			case 'q': {
			    for(i=0; i<4 && getchar() == quit[i] ; i++)
                       ;
                if(i==4)
                    estado=QUIT;
                else
                    estado=ERROR;
			    break;
			}
			default: {
			    while(getchar() != '\n');
			    estado=ERROR;
			}
	    }

return estado;
}

int verifMats(int dim, int ** matAux, int ** matAct)
{
int i, j, distintas=0;

for(i=0; i<dim && distintas==0; i++)
    for(j=0; j<dim && distintas==0; j++)
        if(matAct[i][j] != matAux[i][j])
            distintas=1;

return distintas;
}
