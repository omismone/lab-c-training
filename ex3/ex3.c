/*  
*   RICHIESTA
*   Leggere da due file due vettori.
*   Fare una funzione che ne calcoli il prodotto scalare. Stamparlo.
*   Fare una funzione che ne faccia la somma. Stampare numero elementi sommati e vettore somma in un file di output.
*   Scrivere le due funzioni in due file .c diversi.
*/

#define MAXROWLEN 10
#define MAXARRLEN 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/arraysum.h"
#include "./lib/dotproduct.h"


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


void main(){
    int *arr1;
    arr1 = malloc(MAXARRLEN * sizeof(int));
    int *arr2;
    arr2 = malloc(MAXARRLEN * sizeof(int));

    int size = readArray("./array1.txt", arr1);
    readArray("./array2.txt", arr2);

    int dot_prod = dotProd(arr1, arr2, size);

    printf("dot product: %d\n", dot_prod);

    int *sum;
    sum = malloc(MAXARRLEN * sizeof(int));
    arrSum(arr1, arr2, size, sum);

    //print on file

    FILE *fp;
    fp = fopen("./out.txt","w");
    fprintf(fp, "numeri sommati: %d\n", size);
    fclose(fp);
    fp = fopen("./out.txt","a");
    for(int i=0; i<size; i++){
        fprintf(fp,"%d",sum[i]);
        if(i != size-1)   fprintf(fp,"\n");
    }
    fclose(fp);
    
    
    return;
}