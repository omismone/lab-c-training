/*  
*   RICHIESTA
*   Cambiare l'esercizio 1 in modo che ci sia una struttura vettore. 
*   Fare una funzione che stampi a video un vettore.
*   Fare una funzione che faccia la somma di due vettori letti da due file diversi.
*/

#define MAXROWLEN 10
#define MAXARRLEN 10
#include <stdio.h>
#include <stdlib.h>

/*
*   Sum two arrays of the same length.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @param size The size of the arrays.
*   @param res The pointer to the array where the result has to be saved.
*/
void arrSum(int *arr1, int *arr2, int size, int *res){
    for(int i = 0; i< size; i++)
        res[i] = arr1[i] + arr2[i];
}

/*
*   Read an array from a file containing a integer every line.
*
*   @param path The path of the file containing the array.
*   @param res A pointer to the array where the result has to be saved
*   @return The size of the array.
*/
int readArray(char path[], int *res){
    FILE *fp;
    fp = fopen(path,"r");
    char buf[MAXROWLEN];
    int n_count = 0;
    while(fgets(buf, sizeof(buf), fp) != NULL){
        res[n_count] += atoi(buf);
        n_count += 1;
    }
    fclose(fp);
    return n_count;
}

/*
*   Print an array to stdout.
*
*   @param a The array.
*   @param size The size of the array.
*/
void printArray(int *a, int size){
    printf("[");
    for(int i = 0; i<size; i++){
        if(i == 0)   printf("%d,", a[i]);
        else if(i == size-1)    printf(" %d", a[i]);
        else    printf(" %d,", a[i]);
    }
    printf("]\n");
}

void main(){
    int *arr1;
    arr1 = malloc(MAXARRLEN * sizeof(int));
    int *arr2;
    arr2 = malloc(MAXARRLEN * sizeof(int));

    int size = readArray("./array1.txt", arr1);
    readArray("./array2.txt", arr2);

    int *sum;
    sum = malloc(MAXARRLEN * sizeof(int));
    arrSum(arr1, arr2, size, sum);

    printArray(sum, size);
}