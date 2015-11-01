#include <stdio.h>
#include "getnum.h"
#include <stdlib.h>

#define BLOQUE 10
#define MAX_NOMBRE 36

enum estado {MOVIMIENTO=1, UNDO, QUIT, SAVE, ERROR};

int getline(char *s);
int leerEntrada(char *s, char *nombreArchivo, char *dirVec);

int
main()
{
    char *s, *nombreArchivo;
    char dirVec;
    int estado, j;

    nombreArchivo=malloc(BLOQUE*sizeof(int));
    s=malloc(BLOQUE*sizeof(char));

    estado=leerEntrada(s, nombreArchivo, &dirVec);

    printf("estado %d, direccion %c", estado, dirVec);

    printf("\nEste es el nombre que se guarda:\n");
    for(j=0; nombreArchivo[j]!=0; j++)
        printf("%c", nombreArchivo[j]);

    printf("\n\nAca deberia decir save:\n");
    for(j=0; s[j]!=' '; j++)
        printf("%c", s[j]);
    putchar('\n');

    return 0;
}

int
leerEntrada(char *s, char *nombreArchivo, char *dirVec)
{
    int i, j, k, estado;
    char *aux;

    i=getline(s);

//    printf("/%d/", i);

    if(i==2){
        if(s[0]=='w' || s[0]=='a' || s[0]=='s' || s[0]=='d'){
            *dirVec=s[0];
            estado=MOVIMIENTO;
        }else
            estado=ERROR;

    }else if(i==5){
        if(s[0]=='u' && s[1]=='n' && s[2]=='d' && s[3]=='o')
            estado=UNDO;

        else if(s[0]=='q' && s[1]=='u' && s[2]=='i' && s[3]=='t')
            estado=QUIT;
        else
            estado=ERROR;

    }else{
        if(s[0]=='s' && s[1]=='a' && s[2]=='v' && s[3]=='e' && s[4]==' '){
            estado=SAVE;
            for(j=0, k=5; j<MAX_NOMBRE && s[k]!='\n'; j++, k++){
                    nombreArchivo[j]=s[k];
                    if(j%BLOQUE==0){
                        aux=realloc(nombreArchivo, (j+BLOQUE)*sizeof(char));
                        if(aux==NULL)
                            return 0;
                        else
                            nombreArchivo=aux;
                                }
            }
            nombreArchivo[j]=0;
        }else
            estado=ERROR;
    }

//for(j=0; nombreArchivo[j]!=0; j++)
//        printf("//%c//\t", nombreArchivo[j]);

//printf("++%c++", *dirVec);

return estado;

}

int getline(char *s)
{
    int c, i;
    char *aux;

    i=0;
    while((c=getchar()) != '\n'){
        s[i++]=c;
        if(i%BLOQUE==0){
            aux=realloc(s, (i+BLOQUE)*sizeof(char));
            if(aux==NULL)
                return 0;
            else
                s=aux;
        }
    }
    s[i++]=c;
    s[i]='\0';


//    for(j=0; j<i; j++)
//        printf("//%c//\t", s[j]);

    return i;
}
