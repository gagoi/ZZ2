/**
 * @file main.c
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <math.h>
#include "mt19937ar.h"

/**
 * @def NB_VALUES
 * 
 * @brief Nombre de valeurs de \pi utilisées pour faire les statistiques.
 */
#define NB_VALUES 100000


/**
 * @def NB_POINTS
 * 
 * @brief Nombre de points utilisés pour le calcule de PI via la méthode de Monte-Carlo, lors des statistiques.
 */
#define NB_POINTS 1000000


/**
 * @var t_values
 * @brief Tableau contenant les quantiles pour le calcul de l'intervalle de confiance.
 */
 double t_values[] = {
	12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.308, 2.262, 2.228, 2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 2.074, 2.069, 2.064, 2.060, 2.056, 2.020, 2.048, 2.045, 2.042, 2.021, 2, 1.980, 1.960
};

/**
 * @brief Calcule la valeur de PI en utilisant la méthode de Monte-Carlo.
 * 
 * La méthode de Monte-Carlo utilise un cercle de rayon 1 centré en (0; 0) pour calculer PI.
 * Cette méthode utilise la surface du cercle et celle du carrée pour calculer PI, respectivement PI*r² = PI et c² = 4 où r est le rayon du cercle (1) et c est le coté du carré (2).
 * Le rapport de ces surfaces donne la probabilité que le point généré soit dans le cercle.
 * On peut donc déduire PI de la manière suivante :
 * \f{eqnarray*}{
 * 	p &=& \frac{surface_{cercle}}{surface_{carre}} \\
 * 	\frac{nb\_inner}{nb\_points}  &=& \frac{surface_{cercle}}{surface_{carre}} \\
 * 	\frac{nb\_inner}{nb\_points}  &=& \frac{\pi \times r^2}{c^2} \\
 * 	\frac{nb\_inner}{nb\_points}  &=& \frac{\pi}{4} \\
 * 	4*\frac{nb\_inner}{nb\_points}  &=& \pi \\
 * \f}
 * 
 * @param nbPoints Nombre de points générés pour calculer PI.
 * 
 * @return double Valeur de PI calculée.
 */
double monte_carlo(int nb_points)
{
	double x, y; 		// Coordonnée du point généré
	int i;				// Variable d'itération
	int nb_inner = 0;	// Nombre de point à l'intérieur du quart de cercle trigonométrique 

	for (i = 0; i < nb_points; ++i)
	{
		x = genrand_real1(); // On génère un nouveau point
		y = genrand_real1();
		
		// Si il est dans le cercle, on incrémente le compteur
		if (pow(x, 2) + pow(y, 2) < 1)
			nb_inner++;
	}

	// On renvoie la valeur de PI (explications plus haut)
	return 4.0 * nb_inner / nb_points;
}

/**
 * @brief Réitère la méthode de Monte-Carlo pour en faire des statistiques.
 * 
 * Chaque valeur de \pi utilisée pour les statistiques sera calculée à parti de 1 000 000 000 de points.
 * 
 * @param nbReplicates Nombre de valeur que l'on veut utilisé pour les futures statistiques.
 * @param values Tableau dans lequel on va mettre les valeurs de \pi calculées.
 * 
 * @return double Moyenne de toutes les valeurs calculées.
 */
double replicates_monte_carlo(int nb_replicates, double * values)
{
	int i; 			// Variable d'itération
	double sum = 0;	// Somme de chaque valeur de pi calculée

	for (i = 0; i < nb_replicates; ++i)
	{
		values[i] = monte_carlo(NB_POINTS); // Avec 1 000 000 000 et 100 essais : 3.1415838135
		sum += values[i]; // Mise à jour de la somme
	}

	return sum / nb_replicates; // Calcul de la moyenne
}

/**
 * @brief Calcule de la variance du jeu de valeur.
 * 
 * @param nb Nombre de valeur dans le jeu.
 * @param vals Tableau contenant les valeurs.
 * @param mean Moyenne des valeurs du tableau.
 * 
 * @return double La variance du jeu.
 */
double calc_variance(int nb, double * vals, double mean)
{
	double s = 0; 	// Somme des valeurs
	int i;			// Variable d'itération

	for (i = 0; i < nb; ++i) // Calcul de la somme des carrés des écarts entre chaque valeur et la moyenne 
		s += pow(vals[i] - mean, 2);

	return s / (nb - 1); // Division par le nombre de valeur - 1 pour finir de calculer la variance
}

/**
 * @brief Permet d'obtenir le quantile correspondant au nombre de valeurs que l'on utilisent
 * 
 * Les 30 premières valeurs du tableau sont en accès direct. \n
 * Les suivantes correspondent à des intervalles : \n
 * 	[30; 40[ : case 30 du tableau \n
 * 	[40; 80[ : case 31 du tableau \n
 *  [80; 120[ : case 32 du tableau \n
 *  [120; +inf[ : case 33 du tableau
 * 
 * @param nb Nombre de valeurs utilisées.
 * 
 * @return double Valeur du quantile.
 */
double get_t(int nb)
{
	return t_values[nb <= 30 ? 30 : 
				nb < 40 ? 30 : 
				nb < 80 ? 31 : 
				nb < 120 ? 32 : 
				33 ]; // Accède directement à la bonne case dans le tableau de quantiles.
}

/** 
 * @brief Calcule le rayon de l'intervalle de confiance.
 * 
 * @param nb Nombre de valeur dans le jeu.
 * @param vals Tableau contenant les valeurs du jeu.
 * @param variance Variance du jeu de valeurs.
 * 
 * @return double Rayon de l'intervalle de confiance.
 */
double calc_radius(int nb, double * vals, double variance)
{
	return get_t(nb) * sqrt(variance / nb);
}

/**
 * @brief Calcul de la suite de fibonnaci de manière itérative.
 * 
 * @param n Indice de l'élément que l'on veut calculer
 * @param vals Liste des valeurs de la suite de fibonnaci jusqu'a l'élément n.
 * @return unsigned long Valeur numéro n de la suite de fibonacci.
 */
unsigned long fibo(int n, unsigned long * vals)
{
	int i; // Variable d'itération
	vals[0] = 1; // Initialisation des premières valeurs de la suite.
	vals[1] = 1;

	for (i = 2; i <= n; ++i) // Calcul de toutes les valeurs jusqu'à celle demandée.
		vals[i] = vals[i - 1] + vals[i - 2];

	return vals[n]; // Renvoie de la valeur demandée.
}

/**
 * @brief Point d'entrée du programme.
 * 
 * Tout d'abord nous avons besoin d'initialiser le générateur aléatoire.
 * 
 * Nous répondons ensuite aux questions du sujet dans l'ordre.
 * 
 * @return int 
 */
int main()
{
	double values[NB_VALUES]; 	// Valeurs de PI calculées par la méthode de Monte-Carlo
	unsigned long fib[100]; 	// Valeurs de la suite de Fibonacci
	int i;						// Variable d'itération
	double mean;				// Moyenne de values
	double variance;			// Variance de values
	double r;					// Rayon de l'intervalle de confiance de values
	double minR, maxR;			// Intervalle de confiance de values

	// Initialisation du générateur de nombre pseudo-aléatoire
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

	printf("Nombre de valeurs : %d\n Nombre de points : %d\n\n", NB_VALUES, NB_POINTS); // Affichage des paramètres utilisés pour obtenir le résultat suivant

	printf("Question 1 : \n");

	printf("PI (%10d) : %.10lf\n",1000, monte_carlo(1000)); // Calcule de Pi par la methode de Monte-Carlo avec 1 000 points
	printf("PI (%10d) : %.10lf\n",1000000, monte_carlo(1000000)); // Calcule de Pi par la methode de Monte-Carlo avec 1 000 000 points
	printf("PI (%10d) : %.10lf\n",1000000000, monte_carlo(1000000000)); // Calcule de Pi par la methode de Monte-Carlo avec 1 000 000 000 points

	printf("Question 2 : \n"); // A partir de maintenant chaque génération de Monte-Carlo se fera avec NB_POINTS points

	mean = replicates_monte_carlo(NB_VALUES, values); // Calcul de Pi comme étant la moyenne des valeurs données par NB_VALUES génération de Monte-Carlo
	printf("Mean : %.10f\n", mean); // Affichage de la moyenne calculée
	
	printf("Question 3 : \n");

	variance = calc_variance(NB_VALUES, values, mean); // Calcul de la variance du jeu de valeur
	r = calc_radius(NB_VALUES, values, variance); // Calcul du rayon de l'intervalle de confiance
	minR = mean - r; // Calcul de l'intervalle de confiance
	maxR = mean + r;

	printf("Var : %.10f\nR : %.10f\n[%.10f;%.10f]\n", variance, r, minR, maxR); // Affichage des valeurs calculées pour la question 3

	printf("Question 4 : \n");
	fibo(95, fib); // Calcul des 96 premières valeurs de la suite de Fibonacci

	for (i = 0; i < 10; ++i) // Affichage des 10 dernières valeurs calculées
		printf("Fibo[%d] = %lu\n", 85 + i, fib[85 + i]);

	return 0;
}