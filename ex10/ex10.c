/*
*   RICHIESTA
*
*   Da una matrice con numeri casuali ordinare con la qsort in ordine crescente le righe pari, e in ordine decrescente quelle dispari. index righe parte da 1.
*/


#define MAXFILEROWLEN 11 //based on integer limits
#define MAXRANDOMNUMBER 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
*   Matrix structure that contains the matrix and its size. //optimizing memory access.
*/
struct matrix{
    int *val;   // The values.
    int size[2];    // size[0] # of rows, size[1] # of cols.
};

/*
*   Generate a random matrix.
*
*   @param mat The matrix.
*/
void getRandomMat(struct matrix *mat){
    srand(time(NULL));   // initialization
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            mat->val[i*mat->size[1]+j] = rand() % MAXRANDOMNUMBER;
        }
    }
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

int ascending(const void *a, const void *b){
    return *(int *)a - *(int *)b;   //  < 0 if a < b, 0 if equals, >0 if a > b
}

int descending(const void *a, const void *b){
    return *(int *)b - *(int *)a;   //    > 0 if a < b, 0 if equals, <0 if a > b
}
/*
*   Order an integers matrix, ascending order for even rows and descending one for odd ones.
*
*   @param mat The matrix.
*/
void sortMatEvenOdd(struct matrix *mat){
    for(int i=0; i<mat->size[0]; i++){
        if(i%2 != 0) qsort(&mat->val[i* mat->size[1]], mat->size[1], sizeof(int), ascending);
        else qsort(&mat->val[i* mat->size[1]], mat->size[1], sizeof(int), descending);
    }
}

void main(){
    struct matrix mat;
    mat.size[0] = 3;
    mat.size[1] = 3;
    mat.val = malloc(sizeof(int) * mat.size[0] * mat.size[1]);
    
    puts("random matrix:");
    getRandomMat(&mat);
    printMatrix(&mat);

    sortMatEvenOdd(&mat);
    puts("\nordered:");
    printMatrix(&mat);

    free(mat.val);
}