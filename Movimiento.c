void movimiento(char * c, int dim, int ** matriz)
{
int i, j, k, l;
/*
de atras para adelante... { if( ! 0 ) then { if(match) { num*2 ; "free"(elDeSobra)... rellenar con ceros ; } } }
*/
switch(*c) {
    case 'd': {
        for(i=0; i<dim; i++)
            for(j=dim-1; j>=0; j--) {
                if(matriz[i][j] != 0) {
                    siCoincideD(i, j, matriz);
                    if(j!=dim-1) {
                        l=j;
                        for(k=j+1; k<dim && l<dim-1; k++, l++)
                            if(matriz[i][k]==0) {
                                matriz[i][k]=matriz[i][l];
                                matriz[i][l]=0;
                            }
                    }
                }
            }
            break;
}
    case 'a': {
            for(i=0; i<dim; i++)
                for(j=0; j<dim; j++) {
                    if(matriz[i][j] != 0) {
                        siCoincideA(i, j, matriz, dim);
                        if(j!=0) {
                            l=j;
                            for(k=j-1; k>=0 && l>0; k--, l--)
                                if(matriz[i][k]==0) {
                                    matriz[i][k]=matriz[i][l];
                                    matriz[i][l]=0;
                                }
                        }
                    }
                }
                break;
    }
    case 'w': {
        for(j=0; j<dim; j++)
            for(i=0; i<dim; i++) {
            }
        break;
    }
    case 's': {
        for(j=0; j<dim; j++)
            for(i=dim-1; i>=0; i--) {
            }
        break;
    }

}
}
