/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */
















/* Genere un reel entre a et b */
double uniform(double a, double b)
{
    return (genrand_real1() * (b - a)) + a;
}

/*
void simulatePopulation(int* numberOfPersons, int numberOfIterations)
{
    int i;
    double fgen;

    for(i = 0; i < numberOfIterations; i++)
    {
        fgen = genrand_real1();
        if(fgen < 0.5)
            numberOfPersons[0]++;
        else if(fgen < 0.6)
            numberOfPersons[1]++;
        else
            numberOfPersons[2]++;
    }
}

int main()
{
    int number = 1000000;
    int persons[3] = { 0, 0, 0 };

    // Tests sur les classes
    printf("Simulation de population: %d\n", number);
    simulatePopulation(persons, number);
    printf("%10.8f\n%10.8f\n%10.8f\n\n", (double)persons[0] / number, (double)persons[1] /number, (double)persons[2] / number);

    return 0;
}
*/

/* Genere a partir d'un tableau de probabilites cumulees un tableau contenant le nombre d'individu dans chaque classe et
un tableau contenant le pourcentage d'individus dans chaque classe */
void simulatePopulation(double* cumulatedProbabilities, int* numberOfPersons, int numberOfIterations)
{
    int i, j;
    double fgen;

    for (i = 0; i < numberOfIterations; i++)
    {
        // Generation du nombre aleatoire entre 0 et 1
        fgen = genrand_real1();

        // Determination de la classe du nombre genere
        j = 0;
        while (fgen >= cumulatedProbabilities[j])
            j++;
        numberOfPersons[j]++;
    }
}

/* Genere a partir d'un tableau de nombre d'individus par classe un tableau contenant les probabilites de chaque classe et
un tableau contenant les probabilites cumulees */
void classProbabilities(int numberOfClasses, int* numberOfPersons, double* probabilities, double* cumulatedProbabilities)
{
    int i, total = 0;

    // Calcul du nombre total d'individu
    for (i = 0; i < numberOfClasses; i++)
        total += numberOfPersons[i];

    if (numberOfClasses > 0)
    {
        // Calcul des probabilites et des probabilites cumulees de chaque classe
        probabilities[0] = (double)numberOfPersons[0] / total;
        cumulatedProbabilities[0] = probabilities[0];
        for (i = 1; i < numberOfClasses; i++)
        {
            probabilities[i] = (double)numberOfPersons[i] / total;
            cumulatedProbabilities[i] = cumulatedProbabilities[i - 1] + probabilities[i];
        }
    }
}

/* Genere un nombre aleatoire selon un distribution negative exponentielle */
double nexp(double m)
{
    return -m * log(1 - genrand_real1());
}

/* Genere a partir d'un tableau de nombre d'individus un tableau contenant le pourcentage de chaque classe */
void getpercentage(int numberOfFrequencies, int numberOfIterations, int* frequencies, double* percentage)
{
    int i;
    for (i = 0; i < numberOfFrequencies; i++)
    {
        percentage[i] = (double) frequencies[i] / numberOfIterations * 100;
    }   
}

/* Genere 2 nombres aleatoires avec la methode Box and Muller pour suivre une distribution gaussienne centree reduite */
void BoxAndMuller(double* x1, double* x2)
{
    double Rn1 = genrand_real1();
    double Rn2 = genrand_real1();

    *x1 = cos(2 * M_PI * Rn2) * sqrt(-2 * log(Rn1));
    *x2 = sin(2 * M_PI * Rn2) * sqrt(-2 * log(Rn1));
}

/* Utilise Box and Muller pour générer deux nombres suivant une distribution gaussienne avec une esperance et un ecart-type */
void gaussianDist(double mean, double sdDev, double* x1, double* x2)
{
    double centredReducedX1, centredReducedX2;
    
    BoxAndMuller(&centredReducedX1, &centredReducedX2);
    *x1 = sdDev * centredReducedX1 + mean;
    *x2 = sdDev * centredReducedX2 + mean;
}


int main(void)
{
    int i, ind, number = 1000000;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);


    double  testSimu_percentages[3]      = { 0, 0, 0 };
    double  testSimu_cumulatedProba[3]  = { 0.5, 0.6, 1 };
    int     testSimu_persons[3]         = { 0, 0, 0 };

    double  testProba_probas[3]         = { 0, 0, 0 };
    double  testProba_cumuProbas[3]     = { 0, 0, 0 };

    int     testNexp_20Bins[20];
    double  testNexp_percentages[20];
    for (i = 0; i < 20; i++) testNexp_20Bins[i] = 0;

    double  x1, x2;
    int     testBoxAndMuller_7Bins[7];
    double  testBoxAndMuller_percentages[7];
    for (i = 0; i < 7; i++) testBoxAndMuller_7Bins[i] = 0;

    double  x1_g, x2_g;
    int     testGaussian_20Bins[20];
    double  testGaussian_percentages[20];
    for (i = 0; i < 20; i++) testGaussian_20Bins[i] = 0;


    /*
    // Tests de la fonction uniform
    printf("1000 sorties de uniform(12.3256 , 27.7896)\n");
    for (i = 0; i < 1000; i++)
    {
        printf("%10.8f ", uniform(12.3256 , 27.7896));
        if (i%5==4) printf("\n");
    }
    */

    // Tests simulation d'une population
    printf("Simulation de population: %d\n", number);
    simulatePopulation(testSimu_cumulatedProba, testSimu_persons, number);
    getpercentage(3, number, testSimu_persons, testSimu_percentages);
    printf("%5.4f %c\n%5.4f %c\n%5.4f %c\n\n", testSimu_percentages[0], '%', testSimu_percentages[1], '%', testSimu_percentages[2], '%');

    // Tests probas et probas cumulees a partir de classes
    printf("Probas et probas cumulees:\n");
    classProbabilities(3, testSimu_persons, testProba_probas, testProba_cumuProbas);
    printf("probas: [%1.8f,%1.8f,%1.8f]\n", testProba_probas[0], testProba_probas[1], testProba_probas[2]);
    printf("probas cumulees: [%1.8f,%1.8f,%1.8f]\n\n", testProba_cumuProbas[0], testProba_cumuProbas[1], testProba_cumuProbas[2]);

    // Tests de Negative exponentielle
    printf("Generation nexp\n");
    for(i = 0; i < number; i++)
    {
        ind = (int) nexp(10);
        if (ind >= 0 && ind < 20)
            testNexp_20Bins[ ind ]++;
    }
    getpercentage(20, number, testNexp_20Bins, testNexp_percentages);
    for(i = 0; i < 20; i++)
        printf("%02d: %5.4f %c\n", i, testNexp_percentages[i], '%');
    printf("\n");

    // Tests de Box And Muller
    printf("Box And Muller\n");
    for(i = 0; i < number; i++)
    {
        BoxAndMuller(&x1, &x2);
        ind = (int)x1 + 3;
        if (ind >= 0 && ind < 7)
            testBoxAndMuller_7Bins[ ind ]++;
        ind = (int)x2 + 3;
        if (ind >= 0 && ind < 7)
            testBoxAndMuller_7Bins[ ind ]++;
    }
    getpercentage(7, number * 2, testBoxAndMuller_7Bins, testBoxAndMuller_percentages);
    for(i = 0; i < 7; i++)
        printf("%02d: %5.4f %c\n", i - 3, testBoxAndMuller_percentages[i], '%');
    printf("\n");

    // Tests Gausse
    printf("Gausse M=10, sdDev=3\n");
    for(i = 0; i < number; i++)
    {
        gaussianDist(10, 3, &x1_g, &x2_g);
        ind = (int)x1_g;
        if (ind >= 0 && ind < 20)
            testGaussian_20Bins[ ind ]++;
        ind = (int)x2_g;
        if (ind >= 0 && ind < 20)
            testGaussian_20Bins[ ind ]++;
    }
    getpercentage(20, number * 2, testGaussian_20Bins, testGaussian_percentages);
    for(i = 0; i < 20; i++)
        printf("%02d: %5.4f %c\n", i, testGaussian_percentages[i], '%');

    return 0;
}
