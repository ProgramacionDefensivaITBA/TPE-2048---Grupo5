#include <stdio.h>
#include "getnum.h"
#include <stdlib.h>

int **creaMatriz(int dim);

int main()
{
int **matriz;
int dim, i, j;

do{
    dim=getint("Numero de filas: ");
    if(dim>10)
        printf("El numero de filas no puede superar 10\n");
}while(dim>10);

matriz=creaMatriz(dim);

for(i=0; i<dim; i++)
    for(j=0; j<dim; j++) {
        printf("%d      ", matriz[i][j]);
        if((j+1)%dim==0)
            printf("\n");
    }
return 0;
}

int **creaMatriz(int dim)
{
int **matriz;
int i;

matriz=calloc(dim, sizeof(*matriz));

if(matriz==NULL)
    return NULL;
else {
    for(i=0; i<dim; i++) {
        matriz[i]=calloc(dim, sizeof(matriz));
        /*usar un aux*/

        if(matriz[i]==NULL)
        /*hacer los frees*/
            return NULL;
    }
}

return matriz;
}
