#include <stdio.h>

void movimiento(char dirVec);

int
main(void)
{
char dirVec, enter;

printf("Ingrese la direccion en la que se realiza el movimiento");
do {
  dirVec = getchar();
  enter = getchar();
  if(enter != '\n' || dirVec!='w' || dirVec!='a' || dirVec!='s' || dirVec!='d') {
    printf("Comando no reconocido\n");
    while(getchar() != '\n');
} while(enter != '\n' || dirVec!='w' || dirVec!='a' || dirVec!='s' || dirVec!='d')
/* Hasta aca es solo el input... ahora hay que hacer el movimiento */


return 0;
}
