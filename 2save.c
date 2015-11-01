#include "2048Back.h"
#include <stdlib.h>
#include <stdio.h>
#define GUARDADO_INVALIDO 8

int
GuardarPartida(char * nombreArchivo, juegoT wtf){
/*Guarda la partida y devuelve el tipo de error*/

    FILE * pPartida;
    int i;
    pPartida = fopen(nombreArchivo,"w");
    if(pPartida == NULL)return GUARDADO_INVALIDO;

//    LimpiaTablero(juegoT);

    fwrite(&juegoT.matActual, sizeof(juegoT.matActual), 1, pPartida);
    fwrite(&juegoT.cantUndos,sizeof(juegoT.cantUndos),1,pPartida);
    fwrite(&juegoT.puntaje,sizeof(juegoT.puntaje),1,pPartida);
    fwrite(&juegoT.dim,sizeof(juegoT.dim),1,pPartida);
    fwrite(&juegoT.condGanar,sizeof(juegoT.condGanar),1,pPartida);

    for(i = 0; i < juegoT.dim ; i++){

        fwrite(juegoT.matActual[i],sizeof(juegoT.matActual[0][0]),juegoT.dim, pPartida);
    }

    fclose(pPartida);

    return SIN_ERRORES;
}



int
CargarPartida(char * nombreArchivo,tipoError *error){
/*Devuelve una partida, modifica 'error' si lo hubo*/

    FILE * pPartida;
    int i;
    partida juegoT;

    pPartida = fopen(nombreArchivo,"r");
    if(pPartida == NULL) {
        *error = LECTURA_INVALIDA;
        return juegoT;
    }else{
        fread(&juegoT.matActual, sizeof(juegoT.matActual),1,pPartida);
        fread(&juegoT.cantUndos,sizeof(juegoT.cantUndos),1,pPartida);
        fread(&juegoT.puntaje,sizeof(juegoT.puntaje),1,pPartida);
        fread(&juegoT.dim,sizeof(juegoT.dim),1,pPartida);
        fread(&juegoT.condGanar,sizeof(juegoT.condGanar),1,pPartida);

        juegoT.matActual = creaMatriz(juegoT.dim);
            for (i=0; i<juegoT.dim ; i++)
                fread(juegoT.matActual[i],sizeof(juegoT.matActual[0][0]),juegoT.dim,pPartida);
            }
        }
    }
    if(getc(pPartida) != EOF)*error = ARCHIVO_INVALIDO;
    fclose(pPartida);
    return juegoT;

}
