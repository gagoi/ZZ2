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

std::normal_distribution<> RabbitFemale::dist_birth(4.5, 9);
std::normal_distribution<> RabbitFemale::dist_nb_litters(6, 1);
std::uniform_int_distribution<short> RabbitFemale::dist_gender(1, 2);

/**
 * @brief Construction d'un nouveau Rabbit Female:: Rabbit Female 
 * 
 * @param week_offset décalage entre l'échelle temporelle de la simulation et celle du lapin.
 */
RabbitFemale::RabbitFemale(unsigned int week_offset):Rabbit(week_offset)
{
	// Lancement de la génération des portées
	init_birth();
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
 * Pour optimiser les calculs, on génère la date de la prochaine portée, et on passe 
 * directement à cette portée (en comptant le temps de gestations). Ainsi on évite de 
 * faire des testes chaque semaine.
 */
void RabbitFemale::init_birth()
{
	// Pour chaque semaine entre la maturitée et la mort de la belle lapine
	for (unsigned int i = _maturity_week; i <= _death_week;)
	{
		// Génération de la date de la prochaine portée
		unsigned short w = dist_birth(generator);
		// On passe directement à la date de cette portée 
		// et on ajoute le temps de gestation
		i += w + GESTATION_DURATION;
		// Si la lapine n'est pas morte avant
		if (i <= _death_week)
		{
			// Création de la portée
			litter * l = new litter;
			l->males = 0;
			l->females = 0;
			l->week = i + _week_offset;
			// Génération des laperaux
			short nb_baby= dist_nb_litters(generator);
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
void RabbitFemale::give_birth(unsigned int week, std::list<Rabbit*>& males, std::list<RabbitFemale*>& females)
{
	// Si la lapine attends encore des portées
	// et que la prochaine tombe cette semaine
	if (!litters.empty() && litters.front()->week == week)
	{
		// Naissance des mâles
		for (short i = 0; i < litters.front()->males; i++)
			males.push_back(new Rabbit(week));
		// Naissance des femelles
		for (short i = 0; i < litters.front()->females; i++)
			females.push_back(new RabbitFemale(week));
		
		// Suppression de la portée de la file
		delete litters.front();
		litters.pop();
	}
}