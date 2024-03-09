/*  
*   RICHIESTA
*   Cambiare l'esercizio 1 in modo che ci sia una struttura vettore. 
*   Fare una funzione che stampi a video un vettore.
*   Fare una funzione che faccia la somma di due vettori letti da due file diversi.
*/

#define MAXROWLEN 10
#define MAXARRLEN 100
#include <stdio.h>
#include <stdlib.h>

/*
*   Array structure that contains the array and its size.
*/
struct vec{
    int *val;   // The array.
    int size;    // Number of its elements.
};

/*
*   Sum two arrays of the same length.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @param res The location where the result has to be saved.
*/
void arrSum(struct vec arr1, struct vec arr2, struct vec *res){
    if(arr1.size != arr2.size) exit(1);
    res->val = malloc(arr1.size * sizeof(int));
    if(res->val == NULL) exit(1);
    res->size = arr1.size;
    for(int i = 0; i< arr1.size; i++)
        res->val[i] = arr1.val[i] + arr2.val[i];
}

/*
*   Read an array from a file containing an integer every line.
*
*   @param path The path of the file containing the array.
*   @param arr The location to save the array.
*/
void readArray(char path[], struct vec *arr){
    FILE *fp;
    fp = fopen(path,"r");
    char buf[MAXROWLEN];
    int r_count = 0;
    arr->val = malloc(MAXARRLEN * sizeof(int));
    if(arr->val == NULL) exit(1);
    while(fgets(buf, sizeof(buf), fp) != NULL){
        arr->val[r_count] = atoi(buf);
        r_count += 1;
    }
    arr->size = r_count;
    fclose(fp);
}

/*
*   Print an array to stdout.
*
*   @param a The array.
*/
void printArray(struct vec a){
    printf("[");
    for(int i = 0; i<a.size; i++){
        if(i == 0)   printf("%d,", a.val[i]);
        else if(i == a.size-1)    printf(" %d", a.val[i]);
        else    printf(" %d,", a.val[i]);
    }
    printf("]\n");
}

void main(){
    //read
    struct vec *arr1;
    arr1 = malloc(sizeof(struct vec));
    arr1->val = malloc(MAXARRLEN * sizeof(int));
    readArray("./array1.txt", arr1);
    struct vec *arr2;
    arr2 = malloc(sizeof(struct vec));
    arr2->val = malloc(MAXARRLEN * sizeof(int));
    readArray("./array2.txt", arr2);

    //optimize memory occupation
    arr1->val = realloc(arr1->val, arr1->size * sizeof(int));
    arr2->val = realloc(arr2->val, arr2->size * sizeof(int));

    //sum
    struct vec *sum;
    sum = malloc(sizeof(struct vec));
    sum->val = malloc(arr1->size * sizeof(int));

    arrSum(*arr1, *arr2, sum);   
    printArray(*sum);

    free(arr1);
    free(arr2);
    free(sum);
}