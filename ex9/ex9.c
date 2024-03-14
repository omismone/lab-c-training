/*
*   RICHIESTA
*
*   Calcolare la trasposta di una matrice.
*/


#define MAXFILEROWLEN 11 //based on integer limits
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*   Matrix structure that contains the matrix and its size. //optimizing memory access.
*/
struct matrix{
    int *val;   // The values.
    int size[2];    // size[0] # of rows, size[1] # of cols.
};


/*
*   Read a matrix from a file allocating contiguous memory spaces. //optimizing memory access speed
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
    if(sscanf(buf, "%d %d", &(mat->size[0]), &(mat->size[1])) != 2) exit(1);
    
    //allocating
    mat->val = malloc(mat->size[0] * mat->size[1] * sizeof(int));
    for(int i=0; i<mat->size[0] * mat->size[1]; i++){
        fgets(buf, sizeof(buf), fp);
        if(buf == NULL) exit(1);
        mat->val[i] = atoi(buf);
    }

    fclose(fp);
}

/*
*   Print a linear matrix to stdout.
*
*   @see The definition of linear matrix at the start of this .c.
*   @param mat The matrix.
*/
void printMatrix(struct matrix *mat){
    for(int i=0; i<(mat->size[0] * mat->size[1]); i++){
        if(i%mat->size[1] == 0) printf("\n");
        printf("%d ", mat->val[i]);
    }
    printf("\n");
}

/*
*   Calculate the transposed of a matrix.
*
*   @param mat The matrix.
*   @param res The place to save the result. 
*/
void transpose(struct matrix *mat, struct matrix *res){
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            res->val[i*res->size[1]+j] = mat->val[j*res->size[1]+i];
        }
    }
}


void main(){
    //in
    struct matrix mat;
    readMatrix("./matrix.txt", &mat);

    //elaborate
    struct matrix res;
    res.size[0] = mat.size[0];
    res.size[1] = mat.size[1];
    res.val = malloc(res.size[0] * res.size[1] * sizeof(int));
    transpose(&mat, &res);

    //out
    printMatrix(&res);
    
    free(mat.val);
    free(res.val);
}