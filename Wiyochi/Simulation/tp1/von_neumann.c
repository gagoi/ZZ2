#include <stdio.h>
#include <stdlib.h>

int powi(int x, int n)
{
	int res = x;
	int i;
	for (i = 0; i < n-1; i++)
	{
		res *= x;
	}
	return res;
}

int suivant(int pred, int taille, int* carre)
{
	*carre = powi(pred, 2);

	int suiv = *carre / powi(10, taille / 2);

	suiv = suiv % powi(10, taille);

	return suiv;
}

int main()
{
	int alea = 3141;
	int carre = 0;
	int i;
	printf("graine: %04d\n", alea);

	for (i = 0; i < 200; i++)
	{
		alea = suivant(alea, 4, &carre);
		printf("%03d: %08d %04d\n", i, carre, alea);
	}

	return 0;
}