/**
 * @file main.cpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier de tests pour les populations de lapins
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <array>
#include "Rabbit.hpp"
#include "Population.hpp"

/**
 * @brief générateur de nombre aléatoire utilisant Mersenne Twister
 */
std::mt19937 generator(456);

/**
 * @brief distribution réelle uniforme entre 0 et 1
 */
std::uniform_real_distribution<>    dis_real_0_1(0.0, 1.0);

/**
 * @brief distribution entière uniforme entre 3 et 6 (nombre de bébés dans chaque portée)
 */
std::uniform_int_distribution<>     dis_int_3_6(3, 6);

/**
 * @brief distribution entière uniforme entre 0 et 11 (mois auquel une femelle enfante)
 */
std::uniform_int_distribution<>     dis_int_0_11(0, 11);

/**
 * @brief distribution entière uniforme entre 5 et 8 (nombre de mois avant la majorité d'un lapin)
 */
std::uniform_int_distribution<>     dis_int_5_8(5, 8);

/**
 * @brief distribution normale (nombre de portées d'une femelle dans l'année)
 */
std::normal_distribution<>          dis_normal_6_1(6, 1);

int main(int argc, char *argv[])
{
    if(argc > 1 && std::string(argv[1]) == std::string("-s"))
    {
        size_t n = (argc > 2 ? atoi(argv[2]) : 10);
        size_t m = (argc > 3 ? atoi(argv[3]) : 50);

        int sum_nbRabbit = 0;
        int sum_death = 0;
        int sum_birth = 0;
        int sum_nbFemale = 0;
        int sum_nbMale = 0;
        double sum_meanDeathAge = 0;

        for (size_t i = 0; i < n; i++)
        {
            Population pop(1000, 1000);
            for (size_t i = 0; i < m; i++)
            {
                pop.passTime(1);
            }
            sum_nbRabbit += pop.getNumberOfRabbit();
            sum_death += pop.getDeath();
            sum_birth += pop.getBirth();
            sum_nbFemale += pop.getNumberOfFemaleRabbit();
            sum_nbMale += pop.getNumberOfMaleRabbit();
            sum_meanDeathAge += pop.getMeanDeathAge();
        }
        std::cout << n << " populations sur " << m << " mois: " << std::endl;
        std::cout << "Moyenne du nombre de lapins:    \t" << static_cast<double>(sum_nbRabbit) / n << std::endl;
        std::cout << "Moyenne du nombre de mâles:     \t" << static_cast<double>(sum_nbMale) / n << std::endl;
        std::cout << "Moyenne du nombre de femelles:  \t" << static_cast<double>(sum_nbFemale) / n << std::endl;
        std::cout << "Moyenne du nombre de morts:     \t" << static_cast<double>(sum_death) / n << std::endl;
        std::cout << "Moyenne du nombre de naissances:\t" << static_cast<double>(sum_birth) / n << std::endl;
        std::cout << "Moyenne des moyennes d'age de mort:\t" << static_cast<double>(sum_meanDeathAge) / n << std::endl;
    }
    else
    {
        size_t n = (argc > 2 ? atoi(argv[2]) : 50);
        std::string filename = std::string(argc > 1 ? argv[1] : "out.txt");
        
        std::ofstream file(filename);
        if(file) file << ""; // efface le contenu du fichier
        std::vector<int> hist(n);

        Population p(1000, 1000);
        std::cout << p;
        for (size_t i = 0; i < n; i++)
        {
            p.passTime(1);
            hist[i] = p.getNumberOfRabbit();
            std::cout << "mois " << i << ": " << p.getNumberOfRabbit() << std::endl;
            p.exportToCSV(filename);
        }
        
        std::cout << p;
        int div = hist[n-1] / 200;

        for (size_t i = 0; i < n; i++)
        {
            printf("%2ld", i);
            std::cout << " " << std::string(hist[i] / div, '*') << std::endl;
        }
    }

    return 0;
}