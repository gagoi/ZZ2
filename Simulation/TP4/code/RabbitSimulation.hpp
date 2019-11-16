#ifndef RABBITSIMULATION_HPP_
#define RABBITSIMULATION_HPP_

#include <iostream>
#include <string>
#include <list>

#include "Rabbit.hpp"
#include "RabbitFemale.hpp"

class RabbitSimulation
{
private:
	std::list<Rabbit*> _males;
	std::list<RabbitFemale*> _females;

	void births();
	void grow();
	void die();

	unsigned int _week;

	// Measurement:
	
	unsigned int nb_rabbits_total;
	unsigned int nb_males_total;
	unsigned int nb_females_total;
	unsigned int nb_childs_deaths;
	unsigned int nb_adults_deaths;

public:
	RabbitSimulation(unsigned int nb_males_init = 2, unsigned int nb_females_init = 2);
	~RabbitSimulation();
	void run(unsigned int week);
	unsigned int get_childs_nb(std::list<Rabbit*> _list);
	unsigned int get_childs_nb(std::list<RabbitFemale*> _list);
};

#endif
