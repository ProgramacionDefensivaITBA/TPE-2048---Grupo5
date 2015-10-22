#include <stdarg.h>

#ifndef _backend2048_h

#define _backend2048_h

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

void liberaMatriz(int i, int **matriz)
/* si no hay espacio para jugar, libera la matriz antes de salir */

#endif // _backend2048_h

