#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

#define SEC_IN_MIN 5
#define MIN_IN_HOUR 2
#define MAX_HOUR 2

void surveilleFork(int pipe[2]);
void secondeFork(int pipeIn[2], int pipeOut[2]);
void minuteFork(int pipeIn[2], int pipeOut[2]);
void heureFork(int pipeIn[2]);

int main()
{
    int surveillePID, secondePID, minutePID, heurePID;
    int pipeSec[2], pipeMin[2], pipeHeu[2];
    pipe(pipeSec);
    pipe(pipeMin);
    pipe(pipeHeu);

    printf("\n");

    surveillePID = fork();

    if (!surveillePID)
    {
        surveilleFork(pipeSec);
    }
    else
    {
        secondePID = fork();
        if (!secondePID)
        {
            secondeFork(pipeSec, pipeMin);
        }
        else
        {
            minutePID = fork();
            if(!minutePID)
            {
                minuteFork(pipeMin, pipeHeu);
            } else
            {
                heureFork(pipeHeu);   
            }
            
        }
        
    }
}

void heureFork(int pipeIn[2])
{
    int min = 0;
    close(pipeIn[1]);
    int cpt = 0;

    int i = 0;
    while (i < MAX_HOUR)
    {
        read(pipeIn[0], &min, sizeof(min));
        ++i;
        printf("%dh\n", i);
    }
}

void minuteFork(int pipeIn[2], int pipeOut[2])
{
    int min = 0;
    close(pipeIn[1]);
    close(pipeOut[0]);
    int cpt = 0;

    int i = 0;
    while (i < MIN_IN_HOUR * MAX_HOUR)
    {
        read(pipeIn[0], &min, sizeof(min));
        ++i;
        printf("\t%dm\n", i);
        if (i == MIN_IN_HOUR)
        {
            write(pipeOut[1], &min, sizeof(min));
            i = 0;
        }
    }
}

void secondeFork(int pipeIn[2], int pipeOut[2])
{
    int sec = 0;
    close(pipeIn[1]);
    close(pipeOut[0]);
    int cpt = 0;

    int i = 0;
    while (i < MIN_IN_HOUR * SEC_IN_MIN * MAX_HOUR)
    {
        read(pipeIn[0], &sec, sizeof(sec));
        ++i;
        printf("\t\t%ds\n", i);
        if (i == SEC_IN_MIN)
        {
            write(pipeOut[1], &sec, sizeof(sec));
            i = 0;
        }
    }
}

void surveilleFork(int pipe[2])
{
    close(pipe[0]);
    int secondePID;
    long j = clock();

    while ((float) (clock() - j) / CLOCKS_PER_SEC < MAX_HOUR * MIN_IN_HOUR * SEC_IN_MIN) {
        long i = clock();
        while ((float) (clock() - i) / CLOCKS_PER_SEC < 1);
        fflush(stdout);
        write(pipe[1], &secondePID, sizeof(secondePID));
    }
}