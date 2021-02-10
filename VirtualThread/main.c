#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("Virtual Thread %d\n", *((int *)arg));
        usleep(100);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t threads[5];

    for (i = 0; i < 5; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, thread_func, arg);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
