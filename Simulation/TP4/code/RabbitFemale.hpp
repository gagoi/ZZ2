/**
 * @file RabbitFemale.hpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief Classe déclarant le comportement d'un lapin mâme.
 * 		  Contient également l'ensembles des distributions nécessaires à la simulation.
 * @version 1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef RABBITFEMALE_HPP_
#define RABBITFEMALE_HPP_

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <cstring>
#include "Rabbit.hpp"

class RabbitFemale : public Rabbit
{
private:
	// Structure d'une portée
	struct litter{
		// Semaine de naissance de la portée
		unsigned int week;
		// Nombre de mâles de la portée
		short males;
		// Nombre de femelles de la portée
		short females;
	};

	// Nombre maximum de portées par an
	static constexpr size_t MAX_LITTERS = 8;

	// Temps de gestation du lapin moyen
	static constexpr ushort GESTATION_DURATION = 4;	

	// Distribution générant la date de la prochaine portée
	static std::normal_distribution<> dist_birth;
	// Distribution générant le nombre de laperaux de la prochaine portée
	static std::normal_distribution<> dist_nb_litters;
	// Distribution générant le sexe de chaque laperau
	static std::uniform_int_distribution<short> dist_gender; 

	// File contenant les portées que la mère aura
	std::queue<litter*> litters;

	// Initialisation des portées
	void init_birth();
public:
	// Créer un lapin femelle
	RabbitFemale(unsigned int week_offset = 0);
	// Libération de la mémoire
	~RabbitFemale();

	// Donne naissance à une portée si nécessaire
	void give_birth(unsigned int week, std::list<Rabbit*>& males, std::list<RabbitFemale*>& females);
};

#endif
