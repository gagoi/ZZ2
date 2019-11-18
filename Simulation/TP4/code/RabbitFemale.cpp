/**
 * @file RabbitFemale.cpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief Classe décrivant le comportement d'une gentille et belle lapine
 * @version 1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "RabbitFemale.hpp"

std::normal_distribution<> RabbitFemale::dist_birth(9, 4);
std::normal_distribution<> RabbitFemale::dist_nb_litters(6.5, 2);
std::uniform_int_distribution<short> RabbitFemale::dist_gender(1, 2);

/**
 * @brief Construction d'un nouveau Rabbit Female:: Rabbit Female 
 * 
 * @param week_offset décalage entre l'échelle temporelle de la simulation et celle du lapin.
 */
RabbitFemale::RabbitFemale(std::mt19937& generator, std::map<int, int>& death_histo, std::map<int, int>& death_period_histo, std::map<int, int>& maturity_histo, std::map<int, int>& gender_histo, std::map<int, int>& baby_histo, std::map<int, int>& delay_histo, unsigned int week_offset):Rabbit(generator, death_histo, death_period_histo, maturity_histo, week_offset),
_gender_histo(gender_histo), _baby_histo(baby_histo), _delay_histo(delay_histo)
{
	// Lancement de la génération des portées
	init_birth();
	log_litters();
}

/**
 * @brief Destruction de l'objet Rabbit Female:: Rabbit Female
 * 
 * Libération de la mémoire allouée aux portées
 */
RabbitFemale::~RabbitFemale()
{
	// Tant qu'il reste des portées
	while (!litters.empty())
	{
		// Libération de la mémoire
		delete litters.front();
		// Suppression de la file
		litters.pop();
	}
}

/**
 * @brief Génère les dates des portées.
 * 
 * 
 * Pour optimiser les calculs, on génère la date de la prochaine portée, 
 * et on passe directement à cette portée (en comptant le temps de gestations).
 * Ainsi on évite de faire des testes chaque semaine.
 */
void RabbitFemale::init_birth()
{
	// Pour chaque semaine entre la maturitée et la mort de la belle lapine
	for (unsigned int i = _maturity_week; i <= _death_week;)
	{
		// Génération de la date de la prochaine portée
		short w;
		do
		{
			w = std::round(dist_birth(generator));
		} while (w < 0 || w > 18);
		// On passe directement à la date de cette portée 
		// et on ajoute le temps de gestation
		i += w;
		// Si la lapine n'est pas morte avant
		if (i <= _death_week)
		{
			// Création de la portée
			litter * l = new litter;
			l->males = 0;
			l->females = 0;
			l->week = i + _week_offset;
			// Génération des laperaux
			short nb_baby;
			do
			{
				nb_baby = dist_nb_litters(generator);
			} while (nb_baby < 4 || nb_baby > 8);
			for (short i = 0; i < nb_baby; i++)
				// Choix de leur sexe
				if (dist_gender(generator) == 1)
					(l->males)++;
				else 
					(l->females)++;
			// Ajout de la nouvelle portée à la liste
			litters.push(l);
		}
	}
}

/**
 * @brief Donne naissance à une portée si nécessaire
 * 
 * @param week date actuelle de la simulation
 * @param males liste des mâles appartenant à la simulation
 * @param females liste des femelles appartenant à la simulation
 */
void RabbitFemale::give_birth(unsigned int week, std::list<Rabbit*>& males, 
	std::list<RabbitFemale*>& females)
{
	// Si la lapine attend encore des portées
	// et que la prochaine tombe cette semaine
	if (!litters.empty() && litters.front()->week == week)
	{
		// Naissance des mâles
		for (short i = 0; i < litters.front()->males; i++)
			males.push_back(new Rabbit(generator, _death_histo, 
			_death_period_histo, _maturity_histo, week));
		// Naissance des femelles
		for (short i = 0; i < litters.front()->females; i++)
		{
			RabbitFemale * rabbit = new RabbitFemale(generator, _death_histo, 
			 _death_period_histo, _maturity_histo,
			 _gender_histo, _baby_histo, _delay_histo, week);
			females.push_back(rabbit);
		}
		
		// Suppression de la portée de la file
		delete litters.front();
		litters.pop();
	}
}

void RabbitFemale::log_litters()
{
	std::queue<litter*> lit;
	unsigned int last_week = get_maturity();

	while (!litters.empty())
	{
		_gender_histo[1] += litters.front()->males;
		_gender_histo[2] += litters.front()->females;
		++_baby_histo[std::round(litters.front()->males + litters.front()->females)];
		_delay_histo[litters.front()->week - last_week]++;
		last_week = litters.front()->week;

		lit.push(litters.front());
		litters.pop();
	}
	while (!lit.empty())
	{
		litters.push(lit.front());
		lit.pop();
	}
}