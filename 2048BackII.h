#include <stdarg.h>

#ifndef _backend2048_h

#define _backend2048_h

#define BORRA_BUFFER while (getchar() != '\n')

typedef struct {
    int **matActual;
    int **matAux;
    int **matMov;
    int cantUndos;
    int puntaje;
    int dim;
    int condGanar;
} juegoT;

int tamMatriz(int dificultad);
/* elige el tamaño de la matriz a partir de la dif*/

int **creaMatriz(int dim);
/* crea la matriz a partir del tamaño que le pases*/

/*funciones de random vistas/hechas en clase*/
double randNormalize(void);
/* numero random entre 0 y 1 inclusive*/
int randInt(int izq, int der);
/* numero random entre el izq y el der usando la funcion randNormalize*/

int calcAzar(void);
/* calcula si ponerle un 2 o el raro caso del 4*/

int nuevoNum(juegoT * pjugada);
/* calcula donde ponerle el nuevo numero */

void liberaMatriz(int i, int **matriz);
/* si no hay espacio para jugar, libera la matriz antes de salir */

void movimiento(char * c, juegoT * pjugada);
/* hace el movimiento de la matriz en la direccion recibida */

void sumaIgualesD(int i, int j, int ** matriz);
/* condicion para que se tengan que "sumar" los numeros */
void sumaIgualesA(int i, int j, int ** matriz, int dim);
void sumaIgualesW(int i, int j, int ** matriz, int dim);
void sumaIgualesS(int i, int j, int ** matriz);


/* verifica si la matriz anterior y la nueva son distintas. Devuelve cero si son iguales */

int cantUndo(int dificultad);
/* designa la cantidad de undos dependiendo la dificultad */

int movDisponibles(juegoT * pjugada);
/* verifica si hay movimientos disponibles. Devuelve 1 si los hay */

int verificaNoNulo(juegoT * pjugada);
/* verifica si el movimieno fue nulo. Devuelve 0 si el movimiento fue nulo */




#endif // _backend2048_h
