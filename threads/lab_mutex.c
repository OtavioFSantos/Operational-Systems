/*Faça um programa que calcule a soma dos elementos de um vetor.
Seu programa deverá receber dois parâmetros: o tamanho de um vetor (>=100) e um número de threads (>=2).
O resultado do programa é o somatório dos elementos deste vetor.
O programa deve criar um vetor do tamanho especificado,
iniciá-lo com valores sintéticos (randomicos ou fixos, por exemplo, 1, 2, 3, ...) e
reparti-lo entre as threads criadas, conforme o número de threads informado.
Por exemplo, se o vetor tiver 100 posições, com 5 threads, então, cada thread irá somar 20 números do vetor.
Orientação a ser seguida: o somatório deve ser realizado em uma variável compartilhada,
sendo utilizado um mutex para coordenar o acesso a ela.*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

typedef struct
{
    int begin, // posição inicial do vetor
        end,   // posição final do vetor
        *v;    // vetor
} Input;

int acum = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *soma(void *par)
{
    int i, somaL;
    Input *in = (Input *)par;
    somaL = 0;
    for (i = in->begin; i < in->end; i++)
        somaL += in->v[i];
    printf("S = %d\n", somaL);
    pthread_mutex_lock(&m);
    acum += somaL;
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(int argc, char **argv)
{
    int i, tam, nthreads, *vet;
    pthread_t *tid;
    Input *dta;

    if (argc != 3)
    {
        fprintf(stderr, "Comando correto: ./lab_mutex <tamanhoVetor> <numeroThreads>\n");
        exit(1);
    }
    if ((tam = atoi(argv[1])) < 100)
    {
        fprintf(stderr, "O tamanho do vetor deve ser maior ou igual à 100.\n");
        exit(1);
    }
    if ((nthreads = atoi(argv[2])) < 2)
    {
        fprintf(stderr, "O numero de threads deve ser maior ou igual à 2.\n");
        exit(1);
    }

    tid = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
    dta = (Input *)malloc(nthreads * sizeof(Input));
    vet = (int *)malloc(tam * sizeof(int));

    for (i = 0; i < tam; ++i)
        vet[i] = 1;

    for (i = 0; i < nthreads; ++i)
    {
        dta[i].v = vet;
        dta[i].begin = i * (tam / nthreads);
        if ((i + 1 == nthreads) && (tam % nthreads != 0))
            dta[i].end = (i + 1) * (tam / nthreads) + tam % nthreads;
        else
            dta[i].end = (i + 1) * (tam / nthreads);
        pthread_create(&(tid[i]), NULL, soma, (void *)&(dta[i]));
    }
    for (i = 0; i < nthreads; ++i)
        pthread_join(tid[i], (void **)NULL);

    printf("Resultado da soma = %d\n", acum);
    free(tid);
    free(dta);
    free(vet);
    return 0;
}