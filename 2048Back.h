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

void liberaMatriz(int i, int **matriz);
/* si no hay espacio para jugar, libera la matriz antes de salir */

void movimiento(char * c, int dim, int ** matriz);
/* hace el movimiento de la matriz en la direccion recibida */

void siCoincide(int i, int j, int ** matriz);
/* condicion para que se tengan que "sumar" los numeros */

int leerEntrada(char nombreArchivo[36], char *dirVec);
/* lee la entrada estandar para saber el proximo movimiento, o paso a seguir que ingresa el usuario */

int verifMats(int dim, int ** matAux, int ** matAct);
/* verifica si la matriz anterior y la nueva son distintas. Devuelve cero si son iguales */

#endif // _backend2048_h
