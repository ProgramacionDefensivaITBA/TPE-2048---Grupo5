#include <stdio.h>
#include "getnum.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "backend2048.h"

int menu(void);
int juegoNuevo(int dificultad);
void anunciaDific(int dificultad);
void imprMatAct(int **matriz, int dim);

/*
typedef? struct {
    int **matActual?;
    int **matAux;
    int cantUndos;
    int score;
}variable?;
*/

int
main()                      // aca esta el main! jaja
{
int dificultad=0, dim, juego=0, estado=0;
int **matAux, **matActual;
char * nombreArchivo[36], *dirVec;
char s;
srand(time(NULL));

printf("    Bienvenido al juego 2048!\n");
printf("\t(Version 1.0)\n");
printf(" By Bortolozzi, Giorgi & Paganini\n");
printf("\n\n\n");

juego=menu();
switch(juego) {
    case 1: {
        putchar('\n');
        dificultad=juegoNuevo(dificultad);
        putchar('\n');
        anunciaDific(dificultad);
        putchar('\n');

        dim=tamMatriz(dificultad);
        matAux=creaMatriz(dim);
        if(matAux==NULL) {
            printf("Oh oh!\nLo lamentamos pero no tiene suficiente espacio para jugar.\n\n");       // SALIMOS ASI NO MAS?
            return 0;
        }
        matActual=creaMatriz(dim);
        if(matActual==NULL) {
            printf("Oh oh!\nLo lamentamos pero no tiene suficiente espacio para jugar.\n\n");       // SALIMOS ASI NO MAS?
            return 0;
        }
        break;
    }
    case 2: {
        printf("Cargando la partida anterior...\n");                         // falta el LOAD FILE aca!!
        return 0;
        break;
    }
    case 3: {
        printf("\n\nGracias por jugar!\n\n");
                                                                            // ACA FALTARIA HACER EL FREE?
        return 0;
    }
}

/* agrego 2 random a la matriz */
nuevoNum(dim, matActual);
nuevoNum(dim, matActual);
/* guardo la nueva en la aux */
matAux=memcpy(matAux, matActual, dim*sizeof(int));
/* la imprimo */
imprMatAct(matActual, dim);
printf("\n\n\n");

/* pido nuevo mov. Undo en 0 */
putchar('\n');
do {
    estado=leerEntrada(nombreArchivo, &dirVec);
    switch(estado) {
        case 1: {
            /* hago el movimiento... si no es NULL, cambio matActual */
            movimiento(&dirVec, dim, matActual);
            putchar('\n');
            imprMatAct(matAux, dim);
/*            if(verifMats(dim, matAux, matActual))     */
                nuevoNum(dim, matActual);
            putchar('\n');
            imprMatAct(matActual, dim);
            printf("\n\n\n");
            putchar('\n');
            putchar('\n');
            break;
        }
        case 2: {
            /* undo() */
            break;
        }
        case 3: {
            /* save(nombreArchivo) */
            break;
        }
        case 4: {
            printf("Desea guardar antes de salir? (y/n)\n");
            do {
                    s=getchar();                                            // ACA HAY ALGO QUE NO FUNCA
                    if(s!='y' || s!='n')
                            printf("Comando no reconocido. Desea guardar antes de salir?  (y/n)");
            } while(s!='y' || s!='n');
            printf("Gracias por jugar!");
            break;
        }
        case 5: {
            printf("\nComando no reconocido.\nLe recordamos que los comandos reconocidos son:\n");
            printf("w, a, s, d -- movimientos\nsave -- guardar\nundo -- volver un paso atras*\nquit -- salir de la partida al menu\n");
            printf("\n(Todos los comandos deben estar seguidos de un enter)\n");
            printf("\n\n* El comando undo no permite hacer 2 undos seguido. ");
            printf("Adicionalmente, si hizo un movimiento que no efectuo cambios, el undo le devolvera la matriz anterior al ultimo cambio.\n\n");
            break;
        }
    }
} while(leerEntrada(nombreArchivo, &dirVec)!=4);  // FALTARIA FIJARSE QUE NO HAYAN LLEGADO A 1024(facil) O A 2048

// aux lo dejo igual por ahora
/* probar usar un flagCambio que este en el movimiento que se prenda si hubo
** un cambio, lo cual significa tmb que hay que guardar la matActual en la
** matAux y habilitar el uso del undo!!!!
*/

return 0;
}

int
menu(void)
{
int opcion=0;
do {
    opcion=getint("\n1. Juego nuevo!\n2. Recuperar un juego grabado.\n3. Salir.\n\n");
    if(opcion != 1 && opcion != 2 && opcion != 3)
        printf("\nOpcion no reconocida! Pruebe devuelta.\n\n");
} while(opcion != 1 && opcion != 2 && opcion != 3);
putchar('\n');
return opcion;
}


int
juegoNuevo(int dificultad)
{
do {
    dificultad=getint("Ingrese la dificultad en la que desea jugar!\n1. Facil\n2. Intermedio\n3. Dificil\n\n");
    if(dificultad != 1 && dificultad != 2 && dificultad != 3)
        printf("\nDificultad no reconocida.\n\n");
} while(dificultad != 1 && dificultad != 2 && dificultad != 3);

return dificultad;
}

void
anunciaDific(int dificultad)
{
switch(dificultad) {
    case 1: {
        printf("Ha seleccionado la dificultad facil!\nLe deseamos suerte!\n");
        break;
    }
    case 2: {
        printf("Ha seleccionado la dificultad intermedio.\nMucha suerte!\n");
        break;
    }
    case 3: {
        printf("Ha seleccionado la dificultad dificil!\nLe deseariamos suerte, pero en nuestra experiencia, no existe tal cosa.\n");
        break;
    }
}
return;
}

void
imprMatAct(int **matriz, int dim)
{
int i, j;
printf("La matriz le quedo asi:\n\n");
for(i=0; i<dim; i++)
    for(j=0; j<dim; j++) {
        printf("%d\t", matriz[i][j]);
        if((j+1)%dim==0)
            printf("\n");
    }
}
