#include <stdio.h>
#include "getnum.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "2048Back.h"

enum estado {MOVIMIENTO=1, UNDO, QUIT, SAVE, ERROR};


void bienvenida(void);
int menu(void);
int juegoNuevo(int dificultad);
void anunciaDific(int dificultad);
void impMatriz(int **matriz, int dim);
int leerEntrada(char nombreArchivo[36], char *dirVec);
int comienzo(int opcion, juegoT * pjugada);
int comienzoJuego(juegoT * pjugada);
int comandos(juegoT * pjugada);

/* como llamar structs segun JuanFra
verifMatriz(&jugada * pjugada;juego);
*/

int
main()                      // aca esta el main
{
srand(time(NULL));

juegoT pjugada;
int juego=0, salir;

bienvenida();
do {
    juego=menu();
    salir=comienzo(juego, &pjugada);
} while(salir!=1);

return 0;
}

void bienvenida(void)
{
printf("    Bienvenido al juego 2048!\n");
printf("\t(Version 1.0)\n");
printf(" By Bortolozzi, Giorgi & Paganini\n");
printf("\n\n");
}

int
menu(void)
{
int opcion=0;
do {
    opcion=getint("\n\n\nMenu Principal\n1. Juego nuevo!\n2. Recuperar un juego grabado.\n3. Salir.\n\n");
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
printf("Ha seleccionado la dificultad ");
switch(dificultad) {
    case 1: {
        printf("facil!\nLe deseamos suerte!\n");
        break;
    }
    case 2: {
        printf("intermedio.\nMucha suerte!\n");
        break;
    }
    case 3: {
        printf("dificil!\nLe deseariamos suerte, pero en nuestra experiencia, no existe tal cosa.\n");
        break;
    }
}
return;
}

int
comienzo(int opcion, juegoT * pjugada)
{
int dificultad=0, salir;

switch(opcion) {
    case 1: {
        putchar('\n');
        dificultad=juegoNuevo(dificultad);
        putchar('\n');
        anunciaDific(dificultad);

        pjugada->cantUndos=cantUndo(dificultad);
        pjugada->dim=tamMatriz(dificultad);

        pjugada->matAux=creaMatriz(pjugada->dim);
        pjugada->matMov=creaMatriz(pjugada->dim);
        pjugada->matActual=creaMatriz(pjugada->dim);

        if( pjugada->matActual == NULL || pjugada->matAux==NULL ||  pjugada->matMov == NULL){
            printf("Oh oh!\nLo lamentamos pero no tiene suficiente espacio para jugar.\n\n");       // SALIMOS ASI NO MAS?
            return 0;
        }
        salir=comienzoJuego(pjugada);
        break;
    }
    case 2: {
        printf("Cargando la partida anterior...\n");                         // falta el LOAD FILE aca!!
        return 0;
        break;
    }
    case 3: {
        salir=1;
        return salir;
    }                                                                // ACA FALTARIA HACER EL FREE?
}
}

int
comienzoJuego(juegoT * pjugada)
{
int salir;
/* agrego 2 random a la matriz */
nuevoNum(pjugada);
nuevoNum(pjugada);

/* guardo la nueva en la actual */
pjugada->matActual=memcpy(pjugada->matActual, pjugada->matMov, (pjugada->dim)*sizeof(int));
/* guardo la nueva en la aux */
pjugada->matAux=memcpy(pjugada->matAux, pjugada->matActual, (pjugada->dim)*sizeof(int));

putchar('\n');
/* imprimo y a jugar */
impMatriz(pjugada->matActual, pjugada->dim);

putchar('\n');
putchar('\n');

salir=comandos(pjugada);

return salir;
}

int
leerEntrada(char nombreArchivo[36], char *dirVec)
{
int turno, c;
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
                    } else{
                    estado=ERROR;
			    }break;
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
                        if(j==35)
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

void
impMatriz(int **matriz, int dim)
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

int
comandos(juegoT * pjugada)
{
char *dirVec;
char * nombreArchivo[36];
int estado=0, salirAMenu, guardar, movDisp, flagUndo=1, movNoNulo=0;
do {
    estado=leerEntrada(nombreArchivo, &dirVec);
    switch(estado) {
        case MOVIMIENTO: {

//        printf("matMov cambia\n");
//        impMatriz(pjugada->matMov, pjugada->dim);
//        printf("matActual no\n");
//        impMatriz(pjugada->matActual, pjugada->dim);
            movimiento(&dirVec, pjugada);
            putchar('\n');
//        printf("matMov cambia\n");
//        impMatriz(pjugada->matMov, pjugada->dim);
//        printf("matActual no\n");
//        impMatriz(pjugada->matActual, pjugada->dim);
            movNoNulo=verificaNoNulo(pjugada);
            if(movNoNulo==1){
                flagUndo=0;
                memcpy(pjugada->matActual, pjugada->matMov, (pjugada->dim)*sizeof(int));

                if(nuevoNum(pjugada)==0);
                    movDisp=movDisponibles(pjugada);
                if(movDisp==0)
                    printf("\n\nPerdiste\n\n");
                putchar('\n');
                impMatriz(pjugada->matActual, pjugada->dim);
                putchar('\n');
            } else {printf("Movimiento nulo\n\n");
             impMatriz(pjugada->matMov, pjugada->dim);}
            //    estado=QUIT;
                break;
            }

        case UNDO: {

            if(pjugada->cantUndos>0 && flagUndo==0){
                memcpy(pjugada->matActual, pjugada->matAux, (pjugada->dim)*sizeof(int));
                pjugada->cantUndos--;
                flagUndo=1;
            }else if(pjugada->cantUndos<=0){
                printf("No hay undos disponibles");
            }else{
                printf("No puede hacer dos undos seguidos");
            }

            break;
        }
        case QUIT: {
            do {
                salirAMenu=getint("\n1. Salir del 2048\n2. Salir al menu principal\n\n");
                if(salirAMenu!=1 && salirAMenu!=2)
                    printf("Comando no reconocido.\n");
            } while(salirAMenu!=1 && salirAMenu!=2);
            do {
                guardar=getint("\nDesea guardar antes de salir?\n1. Si.\n2. No.\n\n");
                if(guardar!=1 && guardar!=2)
                    printf("Comando no reconocido.\n");
            } while(guardar!=1 && guardar!=2);
            if(guardar==1)
                printf("Se ha guardado la partida!\n");         // FALTA GUARDAR
            printf("\nGracias por jugar!\n");
            break;
        }
        case SAVE: {
            /* save(nombreArchivo) */
            break;
        }
        case ERROR: {
            printf("\nComando no reconocido.\nLe recordamos que los comandos reconocidos son:\n");
            printf("w, a, s, d -- movimientos\nsave -- guardar\nundo -- volver un paso atras*\nquit -- salir de la partida al menu\n");
            printf("\n(Todos los comandos deben estar seguidos de un enter)\n");
            printf("\n\n* El comando undo no permite hacer 2 undos seguidos. ");
            printf("Adicionalmente, si hizo un movimiento que no efectuo cambios, el undo le devolvera la matriz anterior al ultimo cambio.\n\n");
            break;
        }
    }

} while(estado!=QUIT);  // FALTARIA FIJARSE QUE NO HAYAN LLEGADO A 1024(facil) O A 2048

return salirAMenu;
}



/* fin del front-end */
