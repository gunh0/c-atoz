#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Allocate memory for an array of integers with size 5
    int size = 5;
    int *arr = (int *)malloc(size * sizeof(int));

    // Check if memory allocation is successful
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Initialize the array with values from 0 to size-1
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    // Print the elements of the array
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory to prevent memory leaks
    free(arr);

    return 0;
}
