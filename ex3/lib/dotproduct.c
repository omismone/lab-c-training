/*
*   Make the dot product of two integers arrays.
*
*   @param arr1 The first array.
*   @param arr2 The second array.
*   @param size The size of the arrays.
*   @return The dot product.
*/
int dotProd(int *arr1, int *arr2, int size){
    int sum = 0;
    for(int i = 0; i< size; i++)
        sum += arr1[i] * arr2[i];
    return sum;
}