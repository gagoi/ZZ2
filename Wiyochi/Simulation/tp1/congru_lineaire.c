#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N_LISTE 10000

int a = 17364;
int c = 1544;
int m = 65521;

int suivant(int prec)
{
    return (a * prec + c) % m;
}

int main()
{
    uint16_t alea = 1000;
    int i;
    int* tab = calloc(sizeof(int), 10);

    printf("graine: %04d\n", alea);

    for (i = 0; i < N_LISTE; i++)
    {
        alea = suivant(alea);
        tab[(int)(((float)alea/m)*10)] += 1;
    }

    for (i = 0; i < 10; i++)
    {
        printf("%d: %08d | %d\%\n", i, tab[i], (100 * tab[i] / N_LISTE));
    }

    free(tab);
    return 0;
}