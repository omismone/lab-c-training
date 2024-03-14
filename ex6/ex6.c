/*
*   RICHIESTA
*   Avendo una matrice con n righe e m colonne, creare un vettore con n elementi.
*   Gli elementi del vettore devono essere casuali tra 0 e m.
*   Creare una funzione che esegua tanti shift logici verso destra, di ciascuna riga, tante volte quanto è il numero casuale nel vettore allo stesso numero di riga.
*/

#define MAXFILEROWLEN 11 //based on integer limits
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
            fprintf(fp, "%d", mat->val[i*mat->size[1]+j]);
            if(j != mat->size[1]-1)  fprintf(fp, " ");
        }
        if(i!=mat->size[0]-1)   fprintf(fp, "\n");
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
*   Generate a random array.
*
*   @param arr The array.
*/
void getRandomVec(struct vec *arr){
    srand(time(NULL));   // initialization
    for(int i=0; i<arr->size; i++){
        arr->val[i] = rand() % arr->size;
    }
}

/*
*   Logic shift an array(right).
*
*   @param p Starting index of the array.
*   @param l The array length.
*   @param n The number of shift.
*/
void shiftVec(int *p, int l, int n){
    for(int k=0; k<n; k++){
        int tmp = p[l-1];
        for(int i=l-1; i>=0; i--){
            p[i] = p[i-1];
        }
        p[0] = tmp;
    }
}

/*
*   Logic shift every row of a matrix a number of time specified in the row of the array.
*   
*   @param mat The original matrix where the result will be placed.
*   @param arr The array.
*/
void shiftMatByVec(struct matrix *mat, struct vec *arr){
    for(int i=0; i<arr->size; i++){
        shiftVec((mat->val) + (i*mat->size[1]), mat->size[1], arr->val[i]);
    }
}

void main(){
    //in
    struct matrix mat;
    readMatrix("./matrix.txt", &mat);
    struct vec arr;
    arr.size = mat.size[0];
    arr.val = malloc(mat.size[0] * sizeof(int));

    //elaborate
    getRandomVec(&arr);
    shiftMatByVec(&mat, &arr);

    //out
    printf("random array: [");
    for(int i=0; i<arr.size; i++){
        printf("%d", arr.val[i]);
        if(i!=arr.size-1) printf(", ");
    }
    printf("]\n");
    printMatrixToFile("./out.txt", &mat);
    
    free(mat.val);
    free(arr.val);
}