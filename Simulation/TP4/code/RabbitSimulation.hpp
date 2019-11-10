#ifndef RABBITSIMULATION_HPP_
#define RABBITSIMULATION_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Rabbit.hpp"
#include "RabbitFemale.hpp"
#include "RabbitChild.hpp"

class RabbitSimulation
{
private:
	std::vector<Rabbit> _males;
	std::vector<RabbitFemale> _females;
	std::vector<RabbitChild> _childs;

	void births();
	void grow();
	void die();
public:
	RabbitSimulation(unsigned int nb_rabbit_init = 2);
	~RabbitSimulation();
};

#endif
