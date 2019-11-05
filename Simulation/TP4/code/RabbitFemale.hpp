#ifndef RABBITFEMALE_HPP_
#define RABBITFEMALE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "Rabbit.hpp"


class RabbitFemale : public Rabbit
{
private:
	static const size_t max_litters = 8; 		// Nombre maximum de portées par an

	unsigned int _weeks_of_birth[max_litters];	// Semaines où il y aura des naissances
	unsigned short _nb_of_litters;				// Nombre de portée qu'il y aura cette année
public:
	RabbitFemale();
};

#endif
