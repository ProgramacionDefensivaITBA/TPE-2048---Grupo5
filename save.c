tipoError
GuardarPartida(char * nombreArchivo, partida partidaActiva){
/*Guarda la partida y devuelve el tipo de error*/

    FILE * pPartida;
    int i;
    pPartida = fopen(nombreArchivo,"w");
    if(pPartida == NULL)return GUARDADO_INVALIDO;

    partidaActiva.turno = partidaActiva.turno % 2 + 1;

    LimpiaTablero(partidaActiva);

    fwrite(&partidaActiva.pvp, sizeof(partidaActiva.pvp),1,pPartida);
    fwrite(&partidaActiva.turno,sizeof(partidaActiva.turno),1,pPartida);
    fwrite(&partidaActiva.filas,sizeof(partidaActiva.filas),1,pPartida);
    fwrite(&partidaActiva.columnas,sizeof(partidaActiva.columnas),1,pPartida);

    for(i = 0; i < partidaActiva.filas ; i++){

        fwrite(partidaActiva.tablero[i],sizeof(partidaActiva.tablero[0][0]),partidaActiva.columnas,pPartida);
    }

    fclose(pPartida);

    return SIN_ERRORES;
}



partida
CargarPartida(char * nombreArchivo,tipoError *error){
/*Devuelve una partida, modifica 'error' si lo hubo*/

    FILE * pPartida;
    int i;
    partida partidaActiva;

    pPartida = fopen(nombreArchivo,"r");
    if(pPartida == NULL) {
        *error = LECTURA_INVALIDA;
        return partidaActiva;
    }else{
        fread(&partidaActiva.pvp, sizeof(partidaActiva.pvp),1,pPartida);
        fread(&partidaActiva.turno,sizeof(partidaActiva.turno),1,pPartida);
        fread(&partidaActiva.filas,sizeof(partidaActiva.filas),1,pPartida);
        fread(&partidaActiva.columnas,sizeof(partidaActiva.columnas),1,pPartida);
        partidaActiva.turno -= 1;

        partidaActiva.tablero = ReservaMemTablero(partidaActiva.filas, partidaActiva.columnas, error);
        if(*error == SIN_ERRORES) {
            for (i=0; i<partidaActiva.filas ; i++){
                fread(partidaActiva.tablero[i],sizeof(partidaActiva.tablero[0][0]),partidaActiva.columnas,pPartida);
            }
        }
    }
    if(getc(pPartida) != EOF)*error = ARCHIVO_INVALIDO;
    fclose(pPartida);
    return partidaActiva;

}
