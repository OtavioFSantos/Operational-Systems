/*Implemente o jogo “pedra-papel-tesoura” onde os jogadores são
threads. Como entrada tem-se a quantidade de rodadas que serão jogadas. Como
saída deve-se apresentar uma mensagem mostrando o placar final.
(1) - Papel, (2) - Tesoura, (3) - Pedra*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int vector[3];
void startJokenpo(int rounds);
void showResults(int vector[]);
void randomNumber(int option);

int main()
{
    int rounds;
    srand(time(NULL));
    printf("How many rounds? ");
    scanf("%d", &rounds);
    startJokenpo(rounds);
}

void startJokenpo(int rounds)
{
    int i = 0, auxRounds = 0, vectorResult[3], rc;
    pthread_t tid[2];
    for (i = 0; i < 3; i++)
    {
        vectorResult[i] = 0;
    }
    while (auxRounds < rounds)
    {
        for (i = 0; i < 2; i++)
            rc = pthread_create(&tid[i], NULL, randomNumber, (int *)i);

        for (i = 0; i < 2; i++)
            pthread_join(tid[i], NULL);

        if (vector[0] == 1 && vector[1] != 2 && vector[1] != vector[0])
            vectorResult[0] += 1;
        else if (vector[0] == 2 && vector[1] != 3 && vector[1] != vector[0])
            vectorResult[0] += 1;
        else if (vector[0] == 3 && vector[1] != 1 && vector[1] != vector[0])
            vectorResult[0] += 1;
        else if (vector[0] == vector[1])
            vectorResult[2] += 1;
        else
            vectorResult[1] += 1;

        auxRounds++;
    }
    showResults(vectorResult);
}

void randomNumber(int option)
{
    vector[option] = (rand() % 2) + 1;
}

void showResults(int vector[])
{
    printf("\nPlayer 1 wins: %d\n", vector[0]);
    printf("Player 2 wins: %d\n", vector[1]);
    printf("Draws: %d\n", vector[2]);
}