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