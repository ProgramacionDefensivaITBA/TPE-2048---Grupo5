#include <stdarg.h>

#ifndef _backend2048_h

#define _backend2048_h

#define BORRA_BUFFER while (getchar() != '\n')

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

void nuevoNum(int dim, int **matriz);
/* calcula donde ponerle el nuevo numero */

void liberaMatriz(int i, int **matriz);
/* si no hay espacio para jugar, libera la matriz antes de salir */

void movimiento(char * c, int dim, int ** matriz);
/* hace el movimiento de la matriz en la direccion recibida */

void siCoincideD(int i, int j, int ** matriz);
/* condicion para que se tengan que "sumar" los numeros */

void siCoincideA(int i, int j, int ** matriz, int dim);

int verifMats(int dim, int ** matAux, int ** matAct);
/* verifica si la matriz anterior y la nueva son distintas. Devuelve cero si son iguales */

#endif // _backend2048_h
