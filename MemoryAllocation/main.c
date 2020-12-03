#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 5;
    int *arr = (int *)malloc(size * sizeof(int)); // 메모리 동적 할당

    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return -1;
    }

    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr); // 메모리 해제

    return 0;
}
