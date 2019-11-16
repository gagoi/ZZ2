#ifndef RABBITFEMALE_HPP_
#define RABBITFEMALE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Rabbit.hpp"


extern std::map<int, int> hist;

class RabbitFemale : public Rabbit
{
private:
	static constexpr size_t MAX_LITTERS = 8; 		// Nombre maximum de portées par an
	static constexpr ushort GESTATION_DURATION = 4;	// Temps de gestation du lapin moyen

	static std::normal_distribution<> dist_birth;
	static std::normal_distribution<> dist_nb_litters;
	static std::uniform_int_distribution<> dist_litters_dates;

	bool _weeks_of_birth[MAX_LIFESPAN];	// Semaines où il y aura des naissances

	void init_birth();
public:
	RabbitFemale();

};

#endif
