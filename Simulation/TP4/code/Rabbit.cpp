/**
 * @file Rabbit.cpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief Classe implémentant le comportement d'un lapin.
 * @version 1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Rabbit.hpp"

std::array<double, 3> Rabbit::intervals
	{14 * WEEK_PER_YEAR, 14 * WEEK_PER_YEAR, MAX_LIFESPAN};
std::array<double, 3> Rabbit::weights {0, 0, 1};

std::mt19937 Rabbit::generator(8);
std::uniform_real_distribution<double> Rabbit::dist_rand(0, 1);
std::uniform_int_distribution<>
	Rabbit::dist_maturity(MATURITY_MIN, MATURITY_MAX);
std::geometric_distribution<int> Rabbit::dist_baby_death(0.1);
std::geometric_distribution<int> Rabbit::dist_maturity_death(0.003);
std::piecewise_linear_distribution<double> Rabbit::dist_death_end
	(Rabbit::intervals.begin(),
	Rabbit::intervals.end(),
	Rabbit::weights.begin());

/**
 * @brief Construction d'un nouveau Rabbit:: Rabbit 
 * 
 * Initialise tous les paramêtres du lapins.
 * 
 * @param week_offset décalage entre l'échelle temporelle de la simulation et celle du lapin.
 */
Rabbit::Rabbit(unsigned int week_offset):
	_age(0), _week_offset(week_offset), _maturity_week(dist_maturity(generator)), _death_week(init_death())
{
}

/**
 * @brief Choisit la date de décès du lapin.
 * 
 * 
 * Il y a 3 possibilités :
 * - Probabilité de 80% de mourir avant la maturité.
 * - Puis probabilité de 50% de mourir avant 11 ans.
 * - Puis oblige la mort avant 15ans.
 * 
 * Pour chacun des cas précédents, on choisira la date de la mort.
 * 
 * @return unsigned int date de la mort du lapin.
 */
unsigned int Rabbit::init_death()
{
	// Chances de mourir avant la maturité
	constexpr double _mortality_before_maturity = 0.8;
	// Chances de mourir entre la maturité et 11 ans
	constexpr double _mortality_before_increments = 0.5;

	// Date de la mort
	unsigned int death_week = 0;

	// dist_rand nous donne un nombre aléatoire entre 0 et 1
	// ainsi si il est inférieur à 0.8, le lapins va mourir avant la maturité (80%)
	if (dist_rand(generator) < _mortality_before_maturity)
		// On génère une date de mort suivant une loi géométrique.
		// Comme la loi géométrique n'est pas bornée, nous répétons le tirage
		// jusqu'à obtention d'une valeur valide
		do
		{
			death_week = dist_baby_death(generator);
		}	
		while(death_week > _maturity_week);
	// Même principe que précédemment mais avec 50%
	else if (dist_rand(generator) < _mortality_before_increments)
		// Même principe que précédemment mais avec d'autres paramètres pour la loi
		do
		{
			// La nombre donné par la distribution appartient à [0; +inf[,
			// On ajoute donc la date de maturité pour bien placer la date de la mort
			death_week = dist_maturity_death(generator) + _maturity_week;
		// On répète tant que l'on n'a pas une date avant les 11 ans
		} while (death_week > 14 * WEEK_PER_YEAR);
	// Si le lapin n'est pas mort avant, on le tue suivant une loi linéaire entre ses 11 et 15 ans
	else 
	{
		death_week = dist_death_end(generator);
	}

	// On renvoie la date de sa mort
	return death_week;
}

/**
 * @brief Fait viellir le lapin
 * 
 * 
 * Comme la date de mort est choisie à la naissance, 
 * pas besoin de faire des générations de nombres aléatoires
 * chaque semaine.
 */
void Rabbit::grow()
{
	// Incrémentation de l'âge du lapin.
	_age++;
}

/**
 * @brief Permet d'obtenir l'âge du lapin.
 * 
 * @return unsigned int âge du lapin.
 */
unsigned int Rabbit::get_age()
{
	return _age;
}

/**
 * @brief Permet d'obtenir la date de maturité du lapin.
 * 
 * @return unsigned int date de maturité du lapin.
 */
unsigned int Rabbit::get_maturity()
{
	return _maturity_week + _week_offset;
}