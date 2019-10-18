#include <stdio.h>
#include <math.h>
#include "mt19937ar.h"

#define NB_VALUES 100
 double t_values[] = {
	12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.308, 2.262, 2.228, 2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 2.074, 2.069, 2.064, 2.060, 2.056, 2.020, 2.048, 2.045, 2.042, 2.021, 2, 1.980, 1.960
};

double monte_carlo(int nbPoints)
{
	double x, y;
	int i, nbInner = 0;

	for (i = 0; i < nbPoints; ++i)
	{
		x = genrand_real1();
		y = genrand_real1();
		//printf("%f %f\n", x, y);
		//if (i == 20) return;
		if (pow(x, 2) + pow(y, 2) < 1)
			nbInner++;
	}

	return 4.0 * nbInner / nbPoints;
}

double replicates_monte_carlo(int nbReplicates, double * values)
{
	int i;
	double sum = 0;

	for (i = 0; i < nbReplicates; ++i)
	{
		values[i] = monte_carlo(10000000); // Avec 1 000 000 000 et 100 essais : 3.1415838135
		sum += values[i];
	}

	return sum / nbReplicates;
}

double calcVariance(int nb, double * vals, double mean)
{
	double s = 0;
	int i;
	for (i = 0; i < nb; ++i)
		s += pow(vals[i] - mean, 2);

	return s / (nb - 1);
}

double getT(int nb)
{
	return t_values[nb <= 30 ? 30 : 
				nb < 40 ? 30 : 
				nb < 80 ? 31 : 
				nb < 120 ? 32 : 
				33 ];
}

double calcRadius(int nb, double * vals, double variance)
{
	return getT(nb) * sqrt(variance / nb);
}

unsigned long fibo(int n, unsigned long * vals)
{
	int i;
	vals[0] = 1;
	vals[1] = 1;

	for (i = 2; i < n; ++i)
		vals[i] = vals[i - 1] + vals[i - 2];

	return vals[n - 1];
}

int main()
{
	// Initialisation du générateur de nombre pseudo-aléatoire
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

	double values[NB_VALUES];
	unsigned long fib[100];
/*
	printf("PI (%10d) : %.10lf\n",1000, monte_carlo(1000));
	printf("PI (%10d) : %.10lf\n",1000000, monte_carlo(1000000));
	printf("PI (%10d) : %.10lf\n",1000000000, monte_carlo(1000000000));
*/

	double mean = replicates_monte_carlo(NB_VALUES, values);
	double variance = calcVariance(NB_VALUES, values, mean);
	double r = calcRadius(NB_VALUES, values, variance);
	double minR = mean - r;
	double maxR = mean + r;

	printf("Mean : %.10f\nVar : %.10f\nR : %.10f\n[%.10f;%.10f]\n", mean, variance, r, minR, maxR);

	printf("Fibo : %lu\n", fibo(90, fib));
}