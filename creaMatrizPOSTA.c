#include <stdio.h>
#include <stdlib.h>

int main(void)
{
int **matriz;
int i, j, k;
int dim=4;

matriz=calloc(dim, sizeof(*matriz));

if(matriz==NULL)
	printf("NULL1\n");
else {
	for(k=0; k<dim; k++) {
		matriz[k]=calloc(dim, sizeof(matriz));
		/*usar un aux*/

		if(matriz[k]==NULL)
		/*hacer los frees*/
		printf("NULL2\n");
	}
}

for(i=0; i<dim; i++)
	for(j=0; j<dim; j++) {
		printf("%4d", matriz[i][j]);
		if((j+1)%4==0)
			printf("\n");
	}

return 0;
}
