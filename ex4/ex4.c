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

#define MAXFILEROWLEN 11 //based on integer limit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*   Matrix structure that contains the matrix and its size.
*/
struct matrix{
    int **val;   // The values.
    int *size;    // size[0] # of rows, size[1] # of cols.
};

/*
*   Read a matrix from a file.
*
*   @see The convention in the first lines of the .c file.
*   @param path The path of the file containing the matrix.
*   @param mat The place to save the matrix.
*/
void readMatrix(char path[], struct matrix *mat){
    FILE *fp;
    fp = fopen(path,"r");
    char buf[MAXFILEROWLEN];
    fgets(buf, sizeof(buf), fp);
    if(buf == NULL) exit(1);
    mat->size = malloc(2 * sizeof(int));
    if(sscanf(buf, "%d %d", &(mat->size[0]), &(mat->size[1])) != 2) exit(1);
    
    mat->val = malloc(mat->size[0] * sizeof(int));
    if(mat->val == NULL)    exit(1);
    for(int i=0; i<mat->size[0]; i++){
        mat->val[i] = malloc(mat->size[1] * sizeof(int));
        if(mat->val[i] == NULL) exit(1);
        for(int j=0; j<mat->size[1]; j++){
            fgets(buf, sizeof(buf), fp);
            if(buf == NULL) exit(1);
            mat->val[i][j] = atoi(buf);
        }
    }
    fclose(fp);
}

/*
*   Print a matrix to stdout.
*
*   @param mat The matrix.
*/
void printMatrix(struct matrix *mat){
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            printf("%d ", mat->val[i][j]);
        }
        printf("\n");
    }
}

/*
*   Free up the memory space used by the matrix.
*
*   @param mat The matrix.
*/
void freeMatrix(struct matrix *mat){
    for(int i=0; i<mat->size[0]; i++){
        free(mat->val[i]);
    }
    free(mat->val);
    free(mat->size);
}

void main(){
    //read
    struct matrix mat;
    readMatrix("./matrix.txt", &mat);

    //print
    printMatrix(&mat);

    freeMatrix(&mat);
}