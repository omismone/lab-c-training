/*
*   RICHIESTA
*   Scrivere una funzione che calcola la media di ogni riga della matrice.
*   Scrivere su file la matrice a media nulla, per calcolarla:
*   1)  calcola media di ogni riga e ottieni un vettore.
*   2)  sottrai vettore ad ogni riga della matrice.
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
*   Matrix structure that contains the matrix and its size.
*/
struct matrix{
    float **val;   // The values.
    int *size;    // size[0] # of rows, size[1] # of cols.
};

/*
*   Array structure that contains the array and its size.
*/
struct vec{
    float *val;   // The array.
    int size;    // Number of its elements.
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
    if(mat->size == NULL) exit(1);
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
*   Calculate the mean of each row of a matrix.
*
*   @param mat The matrix.
*   @param res The place to save the result.
*/
void calculateMeans(struct matrix *mat, struct vec *res){
    res->size = mat->size[0];
    res->val = malloc(res->size * sizeof(float));
    if(res->val == NULL) exit(1);
    for(int i=0; i<res->size; i++){
        float sum = 0;
        for(int j=0; j<mat->size[1]; j++){
            sum += mat->val[i][j];
        }
        res->val[i] = sum/(mat->size[1]);
    }
}

/*
*   Calculate the zero-meaned matrix from a matrix.
*   
*   @param mat The matrix.
*   @param z The zero-meaned matrix.
*/
void calculateZeroMeaned(struct matrix *mat, struct matrix *z){
    z->size = malloc(2 * sizeof(int));
    z->size = mat->size;
    z->val = malloc(z->size[0] * sizeof(float));
    if(z->val == NULL) exit(1);

    struct vec *mean;
    mean = malloc(sizeof(struct vec)); //i need to allocate mean here, if i put the allocation in the function it gives seg fault, WHY? i can't define mean as a normal struct either!
    if(mean == NULL) exit(1);
    calculateMeans(mat, mean);

    for(int j=0; j<mat->size[0]; j++){
        z->val[j] = malloc(z->size[1] * sizeof(float));
        if(z->val[j] == NULL)   exit(1);
        //subtract
        for(int k=0; k<mean->size; k++){
            z->val[j][k] = mat->val[j][k] - mean->val[k];
        }
    }
}

/*
*   Print a matrix in a file. [in the first row print matrix dimensions]
*   
*   @param path The path of the file.
*   @param mat The matrix.
*/
void printMatrixToFile(char path[], struct matrix *mat){
    FILE *fp;
    fp = fopen(path,"w");
    fprintf(fp, "%d %d\n", mat->size[0], mat->size[1]);
    fclose(fp);
    fp = fopen(path, "a");
    for(int i=0; i<mat->size[0]; i++){
        for(int j=0; j<mat->size[1]; j++){
            fprintf(fp, "%.2f", (float)mat->val[i][j]);
            if(j != mat->size[1]-1)  fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


void main(){
    //read
    struct matrix mat;
    readMatrix("./matrix.txt", &mat);

    //calculate
    struct matrix z;
    calculateZeroMeaned(&mat, &z);


    //print
    printMatrixToFile("./out.txt", &z);
    free(*mat.val);
    free(mat.size);
    free(*z.val);
}