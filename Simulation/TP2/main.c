#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415

double genrand_real1(); // Fonction permettant de générer des nombres pseudos aléatoires.

/*
 * Permet d'obtenir un réel appartenant à l'intervalle passé en paramètre.
 */
double uniform(double a, double b)
{
	return genrand_real1() * (b - a) + a;
}

/*
 * Permet de tester une distribution de probabilités en utilisant des probabilités cumulées.
 */
int * histo(int nb_drawing)
{
	int * nb = (int *) calloc(sizeof(int), 3); // Allocation du tableau qui contiendra la solution.
	int i; // Variable d'itération
	double k; // Nombre aléatoire.

	for (i = 0; i < nb_drawing; ++i) // Pour chaque tirage (1 000 ou 1 000 000) :
	{
		k = genrand_real1(); // Génération d'un nombre aléatoire et incrémentation de la bonne case du tableau.
		if (k < 0.5) 
			nb[0]++;
		else if (k < 0.6)
			nb[1]++;
		else
			nb[2]++;
	}
	
	return nb; // Renvoie le tableau.
}

/*
 * Permet de calculer la probabilité de chaque classe à partir d'un nombre d'éléments par classe.
 */
double * calcProb(int nb_classes, int * classes)
{
	int i; // Variable d'itération.
	int s = 0; // Nombre d'éléments total.
	double prob[nb_classes]; // Tableau contenant la probabilité d'être dans une classe. (Pas nécessaire ici, mais intéressant à étudier)
	double * probCum = (double *) malloc(sizeof(double) * nb_classes); // Tableau contenant les probabilités cumulées.


	for (i = 0; i < nb_classes; ++i) // Calcul du nombre d'éléments.
		s += classes[i];

	for (i = 0; i < nb_classes; ++i) // Calcul de la probabilité d'être dans chaque classe.
		prob[i] = (double) classes[i] / s;

	probCum[0] = prob[0]; // Initialisation du tableau de probabilités cumulées.
	for (i = 1; i < nb_classes; ++i) // Calcul du tableau de probabilités cumulées.
		probCum[i] = probCum[i - 1] + prob[i];

	return probCum; // Renvoie du tableau de probabilités cumulées.
}

void showProba(double * prob, int nb_prob)
{
	int i;

	for (i = 0; i < nb_prob; ++i)
		printf("%lf\n", prob[i]);
}

double negativExpDistrib(double m)
{
 	return (-m * log(1 - genrand_real1()));
}

void negativExpDistribBins(double m, int nb_drawing, int * bins)
{
	int i;
	int k;

	for (i = 0; i < nb_drawing; ++i)
	{
		k = (int) negativExpDistrib(m);
		bins[k  > 20 ? 20 : k]++;
	}
}

void montecarlo(double * rand)
{
	double n1 = genrand_real1();
	double n2 = genrand_real1();

	double a = sqrt(-2 * log(n1));

	rand[0] = cos(2 * M_PI * n2) * a;
	rand[1] = sin(2 * M_PI * n2) * a;
}

void measureMonteCarlo(int * measure, int nb_drawing)
{
	int i;
	double t[2];

	for (i = 0; i < nb_drawing; ++i)
	{
		montecarlo(t);
		//printf("%f - %f\n", t[0], t[1]);
		int id1 = t[0] + 3;
		int id2 = t[1] + 3;

		if (id1 < 0 || id1 > 5) measure[6]++;
		else measure[id1]++;

		if (id2 < 0 || id2 > 5) measure[6]++;
		else measure[id2]++;
	}
}

int main()
{
	int i, j; // Variables pour les itérations.
	int * histo1000; // Tableau utilisé pour la question 3 avec 1 000 tirages.
	int * histo1000000; // Tableau utilisé pour la question 3 avec 1 000 000 tirages.
	double * cumul1000; // Tableau utilisé pour stocker l'histogramme des probabilités cumulées avec 1 000 tirages.
	double * cumul1000000; // Tableau utilisé pour stocker l'histogramme des probabilités cumulées avec 1 000 000 tirages.
	int * bins1000 = (int *) calloc(sizeof(int), 21); // Tableau utilisé pour stocker les valeurs de 1 000 tirages suivant la loi exponentielle négative.
	int * bins1000000 = (int *) calloc(sizeof(int), 21); // Tableau utilisé pour stocker les valeurs de 1 000 000 tirages suivant la loi exponentielle négative.
	int  * measure = (int *) calloc(sizeof(int), 7); // Tableau utilisé pour compter les tirages et faire des mesures sur la génération de nombres suivant une loi normale centrée.
	
	printf("Question 2 :\n");
	for(i = 0; i < 10; ++i)
	{
		for (j = 0; j < 10; ++j)
			printf("%f | ", uniform(3, 4));
		printf("\n");
	}

	printf("\nQuestion 3 :\n");
	histo1000 = histo(1000);
	histo1000000 = histo(1000000);

	printf("Histo 1 000 | 1 000 000\n");
	printf("%2.2f (%4d) | %2.2f (%d)\n", (float) histo1000[0] / 1000,  histo1000[0], (float) histo1000000[0] / 1000000,  histo1000000[0]);
	printf("%2.2f (%4d) | %2.2f (%d)\n", (float) histo1000[1] / 1000,  histo1000[1], (float) histo1000000[1] / 1000000,  histo1000000[1]);
	printf("%2.2f (%4d) | %2.2f (%d)\n", (float) histo1000[2] / 1000,  histo1000[2], (float) histo1000000[2] / 1000000,  histo1000000[2]);

	cumul1000 = calcProb(3, histo1000);
	cumul1000000 = calcProb(3, histo1000000);

	printf("\nProbalités cumulées de l'histo à 1 000 tirages :\n");
	showProba(cumul1000, 3);
	printf("\nProbalités cumulées de l'histo à 1 000 000 tirages :\n");
	showProba(cumul1000000, 3);


	printf("\nQuestion 4 :\n");
	negativExpDistribBins(10, 1000 , bins1000);
	negativExpDistribBins(10, 1000000, bins1000000);

	printf("Nb tirages");
	for (i = 0; i < 20; ++i)
		printf(" | [%2d;%2d[", i, i + 1);
	printf(" | [20; +inf [\n%10d", 1000);
	for (i = 0; i < 21; ++i)
		printf(" | %7d", bins1000[i]);
	printf("\n%10d", 1000000);
	for (i = 0; i < 21; ++i)
		printf(" | %7d", bins1000000[i]);

	printf("\n\nQuestion 5: \n");
	measureMonteCarlo(measure, 10000000);
	for (i = 0; i < 6; ++i)
		printf("[%2d;%2d[ : %2.2f (%d)\n", i - 3 ,i - 2,(float) measure[i] / 10000000 * 100, measure[i]);

	free(histo1000);
	free(histo1000000);
	free(cumul1000);
	free(cumul1000000);
	free(bins1000);
	free(bins1000000);
	free(measure);
	return 0;
}