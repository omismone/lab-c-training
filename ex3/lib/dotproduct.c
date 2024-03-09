#include "omislib.h"

/*
*   Make the dot product of two integers arrays.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @return The dot product.
*/
int dotProd(struct vec arr1, struct vec arr2){
    int sum = 0;
    for(int i = 0; i< arr1.size; i++)
        sum += arr1.val[i] * arr2.val[i];
    return sum;
}