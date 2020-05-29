# TPE-2048

-Mostrar Menu                                                     F
-Pide dificultad (1,2,3)                                          F
-Crea el tablero (malloc)                                         B 
-Pone 2 primeros números (11% 4s, 89% 2s, rand)                   B
-Muestra el tablero                                               F
-Pide movimiento al usuario                                       F
-Maquina de estados                                               F
-Funcion Jugada                                                   B
  -Movimiento (w,a,s,d)
    -Guarda tablero anterior en aux (while undo>0)
    -Hace el movimiento
      -Desplazamientos
      -Suma de 2 iguales contiguos
    -Agrega un rand (2 0 4)
    -Muestra el tablero
  -Save archivo
    -Guarda el juegos con un nombre de 35 (o menos char)
  -Quit (pregunta si quiere guardar Y/N)
    -Pregunta si quiere guardar
    -if (Y)
      save
    else sale
  -Undo (Guardar matriz anterior y no puede haber 2 seguidos)
    -Reemplaza matriz principal por aux
    -Undo
    -Muestra matriz
    -No puede hacer otro undo
