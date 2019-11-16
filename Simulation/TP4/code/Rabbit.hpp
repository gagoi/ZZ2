/**
 * @file Rabbit.hpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief Classe déclarant le comportement d'un beau et fort lapin.
 *		  Contient également l'ensembles des distributions nécessaires à la simulation.
 * @version 1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RABBIT_HPP_
#define RABBIT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <array>

class Rabbit
{
protected:
	// Constante du nombre de semaines par an.
	static constexpr unsigned short WEEK_PER_YEAR = 52;
	// Constante de la durée de vie maximum d'un lapin en semaine
	static constexpr unsigned int MAX_LIFESPAN = 15 * WEEK_PER_YEAR;
	// Age en semaine à partir duquel un lapin peut devenir mature 
	static constexpr unsigned int MATURITY_MIN = 4 * 4; 
	// Age en semaine jusqu'auquel un lapin peut devenir mature
	static constexpr unsigned int MATURITY_MAX = 8 * 4; 


	// Générateur de nombres pseudo-aléatoires de Mersenne-Twister
	static std::mt19937 generator;

private:
	// Age en semaine
	unsigned int _age;	
	// Variable d'initialisation d'une distribution 
	// linéaire de piecewise
	static std::array<double,3> intervals;
	static std::array<double,3> weights;

	// Fonction initialisant la mort des lapins
	unsigned int init_death();

protected:
	// Distribution permettant de faire un nombre aléatoire 
	// de type pourcentage
	static std::uniform_real_distribution<> dist_rand;
	// Distribution générant la date de maturité du lapin
	static std::uniform_int_distribution<> dist_maturity;
	// Distribution générant la date de mort d'un lapin adulte
	static std::geometric_distribution<int> dist_maturity_death;
	// Distribution générant la date de mort d'un laperau
	static std::geometric_distribution<int> dist_baby_death;
	// Distribution générant la date de mort d'un papy lapin
	static std::piecewise_linear_distribution<double> dist_death_end;

	// Semaine de décallage entre le temps absolu et le temps du lapin
	unsigned int _week_offset;
	// Age en semaine auquel le lapin sera mature
	unsigned int _maturity_week; 
	// Age en semaine auquel le lapin va mourir
	unsigned int _death_week; 

public:
	// Créer un lapin
	Rabbit(unsigned int week_offset = 0);

	// Fais grandir le lapin
	void grow();
	// Renvoie l'age du lapin en semaine
	unsigned int get_age();
	// Renvoie la date de maturité du lapin
	unsigned int get_maturity();
	// Renvoie la date de mort du lapin.
	inline unsigned int get_death_week() {return _death_week + _week_offset;};
};

#endif
