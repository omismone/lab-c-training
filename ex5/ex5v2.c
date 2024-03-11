/*
*   RICHIESTA
*   Stessa dell'esercizio 5, con la differenza di usare una matrice allocata linearmente.
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

#define MAXFILEROWLEN 11 //based on integer limits
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
*   Matrix structure that contains the matrix and its size. //optimizing memory access linear.
*/
struct linearmatrix{
    float *val;   // The values.
    int size[2];    // size[0] # of rows, size[1] # of cols.
};

/*
*   Array structure that contains the array and its size.
*/
struct vec{
    float *val;   // The array.
    int size;    // Number of its elements.
};


/*
*   Read a matrix from a file allocating contiguous memory spaces. //optimizing memory access speed
*
*   @see The convention in the first lines of the .c file.
*   @param path The path of the file containing the matrix.
*   @param mat The place to save the matrix.
*/
void readLinMatrix(char path[], struct linearmatrix *mat){
    FILE *fp;
    fp = fopen(path,"r");
    char buf[MAXFILEROWLEN];
    fgets(buf, sizeof(buf), fp);
    if(buf == NULL) exit(1);
    if(sscanf(buf, "%d %d", &(mat->size[0]), &(mat->size[1])) != 2) exit(1);
    
    //allocating
    mat->val = malloc(mat->size[0] * mat->size[1] * sizeof(float));
    for(int i=0; i<mat->size[0] * mat->size[1]; i++){
        fgets(buf, sizeof(buf), fp);
        if(buf == NULL) exit(1);
        mat->val[i] = atoi(buf);
    }

    fclose(fp);
}


/*
*   Calculate the mean of each row of a linear matrix.
*
*   @param mat The linear matrix.
*   @param res The place to save the result.
*/
void calculateMeans(struct linearmatrix *mat, struct vec *res){
    for(int i=0; i<res->size; i++){
        float sum = 0;
        for(int j=0; j<mat->size[1]; j++){
            sum += mat->val[i*mat->size[1]+j];
        }
        res->val[i] = sum/(mat->size[1]);
    }
}


/*
*   Calculate the zero-meaned matrix from a linear matrix.
*   
*   @param mat The matrix.
*   @param z The zero-meaned matrix.
*/
void calculateZeroMeaned(struct linearmatrix *mat, struct linearmatrix *z){
    struct vec *mean;
    mean = malloc(sizeof(struct vec)); 
    if(mean == NULL) exit(1);
    mean->size = mat->size[0];
    mean->val = malloc(mean->size * sizeof(float));
    if(mean->val == NULL) exit(1);
    calculateMeans(mat, mean);

    for(int j=0; j<mat->size[0]; j++){
        //subtract
        for(int k=0; k<mean->size; k++){
            z->val[j*z->size[1]+k] = mat->val[j*mat->size[1]+k] - mean->val[k];
        }
    }
}

/*
*   Print a matrix in a file. [in the first row print matrix dimensions]
*   
*   @param path The path of the file.
*   @param mat The matrix.
*/
void printMatrixToFile(char path[], struct linearmatrix *mat){
    FILE *fp;
    fp = fopen(path,"w");
    fprintf(fp, "%d %d\n", mat->size[0], mat->size[1]);
    fclose(fp);
    fp = fopen(path, "a");
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            fprintf(fp, "%.2f", (float)mat->val[i*mat->size[1]+j]);
            if(j != mat->size[1]-1)  fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


/*
*   Print a linear matrix to stdout.
*
*   @see The definition of linear matrix at the start of this .c.
*   @param mat The matrix.
*/
void printLinMatrix(struct linearmatrix *mat){
    for(int i=0; i<(mat->size[0] * mat->size[1]); i++){
        if(i%mat->size[1] == 0) printf("\n");
        printf("%.2f ", mat->val[i]);
    }
    printf("\n");
}


void main(){
    struct linearmatrix mat;
    readLinMatrix("./matrix.txt", &mat);

    //allocate z
    struct linearmatrix z;
    z.size[0] = mat.size[0];
    z.size[1] = mat.size[1];
    z.val = malloc(z.size[0] * sizeof(int*));
    if(z.val == NULL) exit(1);

    calculateZeroMeaned(&mat, &z);

    //print
    printMatrixToFile("./out.txt", &z);
    
    //freeMatrix(&mat);
    free(mat.val);
    free(z.val);
}