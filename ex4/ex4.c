/*
*   RICHIESTA
*   Leggere da file una matrice e stamparla.
*   -----------------------------------------
*   CONVENZIONE
*   Sul file prima la riga contiene dimensioni, in seguito un valore per riga, da sx a dx e da alto in basso.
*   ESEMPIO
*   ⌈1 2 3⌉
*   |4 5 6|     MATRICE
*   ⌊7 8 9⌋ 
*
*   3 3
*   1
*   2
*   3
*   4           FILE
*   5
*   6
*   7
*   8
*   9
*/

#define MAXFILEROWLEN 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*   Read a matrix from a file containing in the first row dimensions(e.g. 3 3 for 3x3 matrixes) and a integer every line(left to right, up to down).
*
*   @param path The path of the file containing the matrix.
*   @param size Pointer to a 2 elements array where to start saving the size of the matrix.
*   @return The matrix.
*/
int **readMatrix(char path[], int *size){
    FILE *fp;
    fp = fopen(path,"r");
    char buf[MAXFILEROWLEN];
    int **mat;
    int rows, cols;
    sscanf(fgets(buf, sizeof(buf), fp), "%d %d", &rows, &cols);
    size[0] = rows;
    size[1] = cols;

    mat = malloc(rows * sizeof(int));
    for(int i=0; i<rows; i++){
        mat[i] = malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++){
            fgets(buf, sizeof(buf), fp);
            mat[i][j] = atoi(buf);
        }
    }
    fclose(fp);
    return mat;
}

/*
*   Print a matrix to stdout.
*
*   @param mat Pointer to the pointer indicating where the matrix starts.
*   @param size Pointer to a 2 elements array that contains the size of the matrix.
*/
void printMatrix(int **mat, int *size){
    for(int i=0; i<size[0]; i++){
        for(int j=0; j<size[1]; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void main(){
    int *size, **mat;
    size = malloc(2 * sizeof(int));
    mat = readMatrix("./matrix.txt", size);
    printMatrix(mat,size);
    free(*mat);
    free(size);
}