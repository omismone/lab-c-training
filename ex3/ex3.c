/*  
*   RICHIESTA
*   Leggere da due file due vettori.
*   Fare una funzione che ne calcoli il prodotto scalare. Stamparlo.
*   Fare una funzione che ne faccia la somma. Stampare numero elementi sommati e vettore somma in un file di output.
*   Scrivere le due funzioni in due file .c diversi.
*
*   CONVENZIONE
*   Tutti i vettori salvati su file hanno nella prima riga un numero che rappresenta la dimensione del vettore, e nelle successive un elemento per riga.
*/

#define MAXROWLEN 11 //based on int limits
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/omislib.h"

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
    char buf[MAXROWLEN];
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


void main(){
    //read
    struct vec *arr1;
    arr1 = malloc(sizeof(struct vec));
    readArray("./array1.txt", arr1);
    struct vec *arr2;
    arr2 = malloc(sizeof(struct vec));
    readArray("./array2.txt", arr2);

    int dot_prod = dotProd(*arr1, *arr2);
    printf("dot product: %d\n", dot_prod);

    //sum
    struct vec *sum;
    sum = malloc(sizeof(struct vec));
    sum->val = malloc(arr1->size * sizeof(int));
    arrSum(*arr1, *arr2, sum); 

    free(arr1);
    free(arr2);
    
    //print on file
    FILE *fp;
    fp = fopen("./out.txt","w");
    fprintf(fp, "%d\n", sum->size);
    fclose(fp);
    fp = fopen("./out.txt","a");
    for(int i=0; i<sum->size; i++){
        fprintf(fp,"%d", sum->val[i]);
        if(i != sum->size-1)   fprintf(fp,"\n");
    }
    fclose(fp);
    
    free(sum);
}