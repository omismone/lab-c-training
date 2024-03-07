/*
*   Leggi un vettore di interi da file e fanne la media (un numero per ogni riga nel file).
*   Attenzione che la media deve essere float.
*/
#define MAXROWLEN 10
#include <stdio.h>
#include <stdlib.h>
void main(){
    FILE *fp;
    fp = fopen("./array.txt","r");
    char buf[MAXROWLEN];
    float sum = 0;
    int row_count = 0;
    while(fgets(buf, sizeof(buf), fp) != NULL){
        sum += atof(buf);
        row_count += 1; 
    }
    fclose(fp);
    printf("%.2f\n", sum/row_count);
}