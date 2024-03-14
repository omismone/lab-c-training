/*
*   RICHIESTA
*   Leggere una matrice da file. Leggere un vettore da file. Eseguire il prodotto matrice vettore.
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
*   Array structure that contains the array and its size.
*/
struct vec{
    int *val;   // The array.
    int size;    // Number of its elements.
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
*   Read an array from a file.
*
*   @see The convention in the first lines of the .c file.
*   @param path The path of the file containing the array.
*   @param arr The location to save the array.
*/
void readArray(char path[], struct vec *arr){
    FILE *fp;
    fp = fopen(path, "r");
    char buf[MAXFILEROWLEN];
    fgets(buf, sizeof(buf), fp);
    if(buf == NULL) exit(1);
    arr->size = atoi(buf);
    arr->val = malloc(arr->size * sizeof(int));
    if(arr->val == NULL) exit(1);
    for(int i=0; i<arr->size; i++){
        fgets(buf, sizeof(buf), fp);
        if(buf == NULL) exit(1);
        arr->val[i] = atoi(buf);
    }
    fclose(fp);
}

/*
*   Calculate matrix array product.
*
*   @param mat The matrix.
*   @param arr The array.
*   @param res The place to save the result.
*/
void prodMatVec(struct matrix *mat, struct vec *arr, struct vec *res){
    memset(res->val, 0, res->size * sizeof(int));
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            res->val[i] += mat->val[i*mat->size[1]+j] * arr->val[j];
        }
    }
}

void main(){
    //in
    struct matrix mat;
    readMatrix("./matrix.txt", &mat);
    struct vec arr;
    readArray("./array.txt", &arr);

    //elaborate
    struct vec res;
    res.size = mat.size[0];
    res.val = malloc(mat.size[1] * sizeof(int));
    prodMatVec(&mat,&arr,&res);

    //out
    printf("product array: [");
    for(int i=0; i<res.size; i++){
        printf("%d", res.val[i]);
        if(i!=res.size-1) printf(", ");
    }
    printf("]\n");
    
    free(mat.val);
    free(arr.val);
    free(res.val);
}