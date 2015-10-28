void siCoincideD(int i, int j, int ** matriz)
{
int k;
for(k=j-1; k>=0; k--) {
    if(matriz[i][j]==matriz[i][k]) {
        matriz[i][j] = matriz[i][j] * 2;
        matriz[i][k] = 0;
        return;
    }
    if(matriz[i][k] != 0 && matriz[i][k] != matriz[i][j])
        return;
}
}

void siCoincideA(int i, int j, int ** matriz, int dim)
{
int k;
for(k=0; k<j; k++) {
    if(matriz[i][k]==matriz[i][j]) {
        matriz[i][k] = matriz[i][k] * 2;
        matriz[i][j] = 0;
        return;
    }
    if(matriz[i][k] != matriz[i][j] && matriz[i][k] != 0)
        return;
}
}
