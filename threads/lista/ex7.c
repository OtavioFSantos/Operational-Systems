/*Faça um programa que programa que gere números inteiros e aleatórios para uma matriz
20x20. Faça uma versão monothread, uma com 2 thread e outra com 4 thread.
Qual possui o menor tempo de execução?*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NUM_THREADS 4

int arr[20][20];

void *generate(void *threadid)
{
    // WHY DOESNT WORK???
    // for (int i = (int)threadid; i < 20; i += (int)threadid)
    //     for (int j = 0; j < 20; j++)
    //         arr[i][j] = rand() % 10;

    switch ((long)threadid)
    {
    case 0:
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 20; j++)
                arr[i][j] = rand() % 10;
        break;

    case 1:
        for (int i = 5; i < 10; i++)
            for (int j = 0; j < 20; j++)
                arr[i][j] = rand() % 10;
        break;

    case 2:
        for (int i = 10; i < 15; i++)
            for (int j = 0; j < 20; j++)
                arr[i][j] = rand() % 10;
        break;

    case 3:
        for (int i = 15; i < 20; i++)
            for (int j = 0; j < 20; j++)
                arr[i][j] = rand() % 10;
        break;

    default:
        printf("Error!");
        break;
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    clock_t begin = clock();
    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&threads[t], NULL, generate, (void *)t);
        if (rc)
            exit(-1);
    }

    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(threads[t], NULL);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n", time_spent);

    // for (int i = 0; i < 20; i++)
    //     for (int j = 0; j < 20; j++)
    //         printf("[%d][%d] = %d\n", i, j, arr[i][j]);

    return 0;
}