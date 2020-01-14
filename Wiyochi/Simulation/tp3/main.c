/**
 * @file main.c
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Implémentations et tests des fonctions créees pour le TP n°3 de Simulation
 * @version 1
 * @date 2019-10-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <math.h>
#include "mt19937ar.h"

/**
 * @brief Tableau des quantiles
 */
const double t_values[] = {
    12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.308, 2.262, 2.228,
    2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086,
    2.080, 2.074, 2.069, 2.064, 2.060, 2.056, 2.052, 2.048, 2.045, 2.042,
    2.021, 2.000, 1.980, 1.960
};

double get_quantil(int ind);
double approx_pi(int number);
double mean_pi(int n, double* pis, int number);
double variance(int n, double* pis, double mean);
void confidences_intervals_95(int n, double mean, double variance, double * b_inf, double * b_sup);
void gen_lapins(int mois, unsigned long* population);

int main()
{
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    int number = 1000000, n = 100, i;
    double pis[n];
    double mean, v, b_inf, b_sup;

    unsigned long lapins[100];

    printf("M_PI: %5.48lf\n\n", M_PI);

    printf("Approximation de PI %d x %d fois:\n", n, number);
    mean = mean_pi(n, pis, number);
    for (i = 0; i < n; i++)
    {
        printf("%5.10f ", pis[i]);
        if (i%5 == 4) printf("\n");
    }
    printf("\n");
    printf("Moyenne -> %5.10f\n", mean);

    v = variance(n, pis, mean);
    printf("Variance -> %5.10f\n", v);

    confidences_intervals_95(n, mean, v, &b_inf, &b_sup);
    printf("Intervalles de confiances: [%5.10f, %5.10f]\n\n", b_inf, b_sup);
    
    printf("Lapins: \n");
    gen_lapins(100, lapins);
    for (i = 0; i < 100; i++)
    {
        printf("Mois %2d: %20lu  ", i, lapins[i]);
        if (i % 3 == 2) printf("\n");
    }
    printf("\n");
    

    return 0;
}

/**
 * @brief Fonction qui permet d'obtenir les quantils à partir du tableau t_values
 * 
 * @param[in] ind indice du quantil voulu ([1, 30], 40, 80, 120, inf)
 * @return double quantil correspondant
 */
double get_quantil(int ind)
{
    int result = 0;
    if (ind <= 30)
        result = ind - 1;
    else if (ind == 40)
        result = 30;
    else if (ind == 80)
        result = 31;
    else if (ind == 120)
        result = 32;
    else
        result = 33;
    
    return t_values[result];
}

/**
 * @brief Fonction permettant d'approximer le nombre PI
 * 
 * @param number Nombre d'itérations sur la méthode Monte-Carlo -> précision du retour
 * @return double Approximation du nombre PI
 */
double approx_pi(int number)
{
    double x, y;
    int i, in = 0;

    // Méthode de Monte-Carlo -> générer des points aléatoires entre 0 et 1 et faire le rapport de points
    // contenus dans le quart de cercle d'origine (0,0) et de rayon 1. Ce rapport est égal à PI / 4.
    for (i = 0; i < number; i++)
    {
        x = genrand_real1();
        y = genrand_real1();

        // Résultats differents en utilisant powf de <math.h>
        //if (pow(x, 2) + pow(y, 2) < 1)    // Resultat avec 1000000000 -> 3.1415453920
        if (x*x + y*y < 1)                // Resultat avec 1000000000 -> 3.1415455080
        {
            in++;
        }
    }
    return (double) in / (double)number * 4;
}

/**
 * @brief Fonction utilisant plusieurs fois la fonction approx_pi() afin d'en faire une moyenne
 * 
 * @param[in] n nombre d'approximations de PI voulu
 * @param[out] pis tableau de taille @a n dans lequel on place les approximations de PI générées
 * @param[in] number nombre d'itérations pour générer chaque approximation avec la fonction approx_pi()
 * @return double moyenne des @a n approximations de PI
 */
double mean_pi(int n, double* pis, int number)
{
    int i;
    double sum = 0;

    // On fait plusieurs approximations de PI sans "redémarrer" le générateur de nombres aléatoires
    for (i = 0; i < n; i++)
    {
        pis[i] = approx_pi(number);
        sum += pis[i];
    }
    return sum / n;
}

/**
 * @brief Fonction calculant une estimation sans biais de la variance d'un tableau (en l'occurence de PI)
 * 
 * @param[in] n taille du tableau fourni
 * @param[in] pis tableau de taille @n contenant les approximations
 * @param[in] mean moyenne des approximations
 * @return double variance des approximations
 */
double variance(int n, double* pis, double mean)
{
    int i;
    double sum = 0;

    for (i = 0; i < n; i++)
    {
        sum += pow(pis[i] - mean, 2);
    }
    return sum / (n - 1);
}

/**
 * @brief Fonction qui calcule les intervalles de confiances à 95%
 * 
 * @param[in] n nombre d'occurences
 * @param[in] mean moyenne
 * @param[in] v variance
 * @param[out] b_inf borne inferieure de l'intervalle de confiance
 * @param[out] b_sup borne supérieur de l'intervalle de confiance
 */
void confidences_intervals_95(int n, double mean, double v, double * b_inf, double * b_sup)
{
    *b_inf = mean - get_quantil(n) * sqrt(v / n);
    *b_sup = mean + get_quantil(n) * sqrt(v / n);
}

/**
 * @brief Fonction générant une population de lapins (Suite de Fibonacci)
 * 
 * @param[in] mois nombre de mois sur lesquels on observe l'évolution de la population de lapins
 * @param[in] long tableau de taille @a mois représentant le nombre de lapins chaque mois
 */
void gen_lapins(int mois, unsigned long* population)
{
    int i;

    population[0] = 1; // On démarre avec 1 couple au temps 0
    population[1] = 1; // Ce même couple se retrouve au temps 1

    for (i = 2; i < mois; i++)
        population[i] = population[i - 1] + population[i - 2];
}