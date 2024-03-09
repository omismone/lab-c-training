#include <stdlib.h>
#include "omislib.h"

/*
*   Sum two arrays of the same length.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @param res The location to save the sum.
*/
void arrSum(struct vec arr1, struct vec arr2, struct vec *sum){
    if(arr1.size != arr2.size) exit(1);
    sum->size = arr1.size;
    for(int i = 0; i< arr1.size; i++)
        sum->val[i] = arr1.val[i] + arr2.val[i];
}