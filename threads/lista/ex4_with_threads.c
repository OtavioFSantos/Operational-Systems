/*Crie um programa para realizar a soma de duas matrizes 50x50 (números
aleatórios). Faça uma abordagem sem uso de pthread, depois crie uma versão com
uso de 2 thread (cada thread irá tratar metade das linhas. Por exemplo, impares x
pares ou as 25 primeiras para um e as restantes para a outra thread).
Compare o tempo de execução de cada uma.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 2

int arr1[50][50], arr2[50][50], sum[50][50];

void *matrix_sum(void *threadid)
{
    if ((long)threadid == 0)
    {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                arr1[i][j] = rand() % 10;
                arr2[i][j] = rand() % 10;
                sum[i][j] = arr1[i][j] + arr2[i][j];
            }
        }
    }
    else if ((long)threadid == 1)
    {
        for (int i = 25; i < 50; i++)
        {
            for (int j = 25; j < 50; j++)
            {
                arr1[i][j] = rand() % 10;
                arr2[i][j] = rand() % 10;
                sum[i][j] = arr1[i][j] + arr2[i][j];
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    clock_t begin = clock();
    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&threads[t], NULL, matrix_sum, (void *)t);
        if (rc)
            exit(-1);
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo: %f\n", time_spent);

    return 0;
}