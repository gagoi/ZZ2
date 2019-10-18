#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NB_RAND 2000000

void vohnNeumann(int seed);
void congruentiel();
unsigned int lfsr();

int main(int argc, char ** argv)
{
	int seed = 1234;
	int i;

	if (argc == 2) seed = atoi(argv[1]);
	else printf("Ajouter un nombre à 4 chiffres en argument pour spécifier la graîne.\n\n");

	if (seed < 0 || seed > 9999) seed = 1234;
	printf("Le seed est : %d\n", seed); 

	//vohnNeumann(seed);
	//congruentiel();

	printf("%d\n", lfsr());

}

void vohnNeumann(int seed)
{
	int i, rand = seed;

	for (i = 0; i < NB_RAND; ++i)
	{
		printf("%03d : 0,%d (%08d)\n", i, rand, rand*rand);
		rand = rand * rand;
		rand %= 1000000;
		rand /= 100;
	}
}

void congruentiel()
{
	/*
	A 16 bits :
		rand = 1000
		m    = 65521
		a    = 17364
		c    = 1544
	A 32 bits :
		rand = 1000
		m    = 4294967291
		a    = 1588635695
		c    = 1544
	*/
	unsigned int rand = 1000; // UTILISER int pour 32 bits, short pour 16.
	unsigned int m = 4294967291;
	unsigned int a = 1588635695;
	unsigned int c = 1544;
	int i;
	int cpt[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (i = 0; i < NB_RAND; ++i)
	{
		rand = (a * rand + c) % m;
	//	printf("%3d : %f\n", i, rand, (float) rand/m*10);
		cpt[(int) ((float) rand/m*10)]++;
	}
	int act = rand;
	int size = 0;
	int flag = 0;
	i = 0;
	do
	{
		rand = (a * rand + c) % m;
		++i;
	} while (rand != act);
	size = i;
	printf("Taille du cycle : %d\n", size);

	for (i = 0; i < 10; ++i)
	{
		printf("%d | ", cpt[i]);
	}
	printf("\n");
	for (i = 0; i < 10; ++i)
	{
		printf("%0.2f |", (float) cpt[i] / NB_RAND);
	}
	printf("\n");
}

unsigned int lfsr()
{
	uint16_t start_state = 0xACE1u;
	uint16_t lfsr = start_state;
	uint16_t bit;
	unsigned int period = 0;

	do
	{
		bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5));
		lfsr = (lfsr >> 1) | (bit << 15);
		++period;
	} while (lfsr != start_state);

	return period;
}