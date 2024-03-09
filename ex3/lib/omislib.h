/*
*   Array structure that contains the array and its size.
*/
struct vec{
    int *val;   // The array.
    int size;    // Number of its elements.
};

int dotProd(struct vec arr1, struct vec arr2);
void arrSum(struct vec arr1, struct vec arr2, struct vec *sum);