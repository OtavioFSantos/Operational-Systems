#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSORS 2

typedef struct process
{
    char name[4];
    int time;
} Process;

typedef struct processor
{
    int amountProcess;
    Process process[5];
} Processor;

int countLines();
int calcTotalTime(int lines);
void readFile(Process process[], int numProc);
void sortProcess(Process process[], int numProc);
void organize(Process process[], int numProc, Processor processor[], int totalTime);
void printResult(Process process[], int numProc, Processor processor[]);

int main()
{
    int numProc, totalTime;
    numProc = countLines();
    totalTime = calcTotalTime(numProc);

    Process process[numProc];
    Processor processor[NUM_PROCESSORS];

    readFile(process, numProc);
    sortProcess(process, numProc);
    organize(process, numProc, processor, totalTime);
    printResult(process, numProc, processor);
    return 0;
}

void printResult(Process process[], int numProc, Processor processor[])
{
    FILE *fp = fopen("SJF_result.txt", "w");

    int auxProcTime = 0;

    for (int i = 0; i < NUM_PROCESSORS; i++)
    {
        auxProcTime = 0;
        fprintf(fp, "Processor %d\n", i + 1);

        for (int j = 0; j < processor[i].amountProcess; j++)
        {
            fprintf(fp, "%s - %d;%d\n", processor[i].process[j].name, auxProcTime, auxProcTime + processor[i].process[j].time);
            auxProcTime += processor[i].process[j].time;
        }
        fprintf(fp, "\n");
    }
}

void organize(Process process[], int numProc, Processor processor[], int totalTime)
{
    int processorTime[NUM_PROCESSORS] = {0};
    int processIndex = 0;

    for (int i = 0; i <= totalTime; i++)
    {
        for (int k = 0; k < NUM_PROCESSORS; k++)
        {
            if (processorTime[k] == i)
            {
                processor[k].process[(processor[k].amountProcess)] = process[processIndex];
                processorTime[k] += process[processIndex].time;
                processor[k].amountProcess++;
                processIndex++;
            }
        }
        if (processIndex >= numProc)
        {
            break;
        }
    }
}

void sortProcess(Process process[], int numProc)
{
    Process aux;
    for (int i = 0; i < numProc; i++)
    {
        for (int j = 0; j < numProc - 1; j++)
        {
            if (process[j].time > process[j + 1].time)
            {
                aux = process[j];
                process[j] = process[j + 1];
                process[j + 1] = aux;
            }
        }
    }
}

int countLines()
{
    int ch = 0, lines = 1;
    FILE *fp = fopen("tasks.txt", "r");
    if (fp == NULL)
    {
        printf("\nERROR: File not found!\n");
        exit(1);
    }

    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }
    fclose(fp);

    return lines;
}

int calcTotalTime(int lines)
{
    int auxtime, total = 0;
    char trash[4];
    FILE *fp = fopen("tasks.txt", "r");

    for (int i = 0; i < lines; i++)
    {
        fscanf(fp, "%s %d", trash, &auxtime);
        total += auxtime;
    }
    fclose(fp);

    return total;
}

void readFile(Process process[], int numProc)
{
    FILE *fp = fopen("tasks.txt", "r");
    for (int i = 0; i < numProc; i++)
    {
        fscanf(fp, "%s %d", process[i].name, &process[i].time);
    }
    fclose(fp);
}