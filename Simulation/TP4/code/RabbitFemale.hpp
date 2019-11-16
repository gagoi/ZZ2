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
	struct litter{
		unsigned int week;
		short males;
		short females;
	};

	static constexpr size_t MAX_LITTERS = 8; 		// Nombre maximum de portées par an
	static constexpr ushort GESTATION_DURATION = 4;	// Temps de gestation du lapin moyen

	static std::normal_distribution<> dist_birth;
	static std::normal_distribution<> dist_nb_litters;
	static std::uniform_int_distribution<> dist_litters_dates;
	static std::uniform_int_distribution<short> dist_gender; 

	std::queue<litter*> litters;

	void init_birth();
public:
	RabbitFemale(unsigned int week_offset = 0);
	~RabbitFemale();

	void give_birth(unsigned int week, std::list<Rabbit*>& males, std::list<RabbitFemale*>& females);

};

#endif
