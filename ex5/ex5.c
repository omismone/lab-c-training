/*
*   RICHIESTA
*   Scrivere una funzione che calcola la media di ogni riga della matrice.
*   Scrivere su file la matrice a media nulla, per calcolarla:
*   1)  calcola media di ogni riga e ottieni un vettore.
*   2)  sottrai vettore ad ogni riga della matrice.
*/

#define MAXFILEROWLEN 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
*   Subtract two arrays of the same length.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @param size The size of the arrays.
*   @param res The pointer to the array where the result has to be saved.
*/
void arrSub(int *arr1, float *arr2, int size, float *res){
    for(int i = 0; i< size; i++)
        res[i] = arr1[i] - arr2[i];
}

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
*   Calculate the mean of each row of a matrix.
*
*   @param mat The matrix.
*   @param size An array of two elements containing # of rows and # of cols.
*   @return An array in which every i-item is the mean of row i of the matrix. 
*/
float *calculateMeans(int **mat, int *size){
    float *means;
    means = malloc(size[0] * sizeof(float));
    for(int i=0; i<size[0]; i++){
        float sum = 0;
        for(int j=0; j<size[1]; j++){
            sum += mat[i][j];
        }
        means[i] = sum/size[1];
    }
    return means;
}

/*
*   Calculate the zero-meaned matrix from a matrix.
*   
*   @param mat The matrix.
*   @size An array of two elements containing # of rows and # of cols.
*   @return The zero-meaned matrix.
*/
float **calculateZeroMeaned(int **mat, int *size){
    float **z;
    float *means;
    means = calculateMeans(mat, size);
    //allocate and calculate
    z = malloc(size[0] * sizeof(float));
    for(int j=0; j<size[0]; j++){
        z[j] = malloc(size[1] * sizeof(float));
        arrSub(mat[j], means, size[0], z[j]);
    }
    return z;
}

/*
*   Print a matrix in a file. [in the first row print matrix dimensions]
*   
*   @param path The path of the file.
*   @param mat The matrix.
*   @param size An array of two elements containing # of rows and # of cols.
*/
void printMatrixToFile(char path[], float **mat, int *size){
    FILE *fp;
    fp = fopen(path,"w");
    fprintf(fp, "%d %d\n", size[0], size[1]);
    fclose(fp);
    fp = fopen(path, "a");
    for(int i=0; i<size[0]; i++){
        for(int j=0; j<size[1]; j++){
            fprintf(fp, "%.2f", mat[i][j]);
            if(j != size[1]-1)  fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void main(){
    int *size, **mat;
    size = malloc(2 * sizeof(int));
    mat = readMatrix("./matrix.txt", size);
    //calculate
    float **z;
    z = calculateZeroMeaned(mat, size);
    //print
    printMatrixToFile("./out.txt", z, size);
    free(*z);
    free(size);
}