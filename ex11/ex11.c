/*
*   RICHIESTA
*
*   Muovere tutti gli elementi di una matrice in alto di due righe e a sinistra di una colonna (rientrando in caso di uscita).
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
*   Logic shift an array(left).
*
*   @param p Starting index of the array.
*   @param l The array length.
*   @param n The number of shift.
*/
void shiftVec(int *p, int l, int n){
    for(int k=0; k<n; k++){
        int tmp = p[0];
        for(int i=0; i<l-1; i++){
            p[i] = p[i+1];
        }
        p[l-1] = tmp;
    }
}

/*
*   Make every item of a matrix go upper by 2 rows and left by 1 col (re-entering).
*
*   @param mat The matrix.
*/
void horseMat(struct matrix *mat){
    //  to get the horse matrix we can divide the problem in 2 steps:
    //  first we shift the entire matrix left of 1 col.
    //  then we have to shift up every row by 2. 
    
    //  there is a way to shift up without matrix or vec buf, transpose, shift left by 2 and transpose again, to achieve it without buffering @see https://en.wikipedia.org/wiki/In-place_matrix_transposition
    //  for our purposes we can be satisfied with an array buffer of short size.

    //shift all to left by 1
    for(int i=0; i<mat->size[0]; i++){
        shiftVec((mat->val) + (i*mat->size[1]), mat->size[1], 1);
    }
    
    int x = 2 * mat->size[1];
    //shift up by 2: we need to save the first x elements, shift all the matrix linear row by x, and then adjust the last x.
    int *tmp;
    tmp = malloc(x * sizeof(int));
    for(int i=0; i<x; i++){
        tmp[i] = mat->val[i];
    }

    for(int i=0; i<(mat->size[0]*mat->size[1])-x; i++){
        mat->val[i] = mat->val[i+x];
    }
    for(int i=0; i<x; i++){
        mat->val[(mat->size[0]*mat->size[1])-x+i] = tmp[i];
    }
    free(tmp);
}


void main(){
    struct matrix mat;
    mat.size[0] = 4;
    mat.size[1] = 3;
    mat.val = malloc(sizeof(int) * mat.size[0] * mat.size[1]);
    
    puts("random matrix:");
    getRandomMat(&mat);
    printMatrix(&mat);

    horseMat(&mat);
    puts("\nhorsed:");
    printMatrix(&mat);

    free(mat.val);
}