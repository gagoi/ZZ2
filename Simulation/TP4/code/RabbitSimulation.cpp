#include "RabbitSimulation.hpp"

RabbitSimulation::RabbitSimulation(unsigned int nb_males_init, unsigned int nb_females_init):
 _week(0)
{
	for (unsigned int i = 0; i < nb_males_init; i++)
		_males.push_back(new Rabbit);
	for (unsigned int i = 0; i < nb_females_init; i++)
		_females.push_back(new RabbitFemale);
}

RabbitSimulation::~RabbitSimulation()
{
	for (auto &&male : _males)
		delete male;
	
	for (auto &&female : _females)
		delete female;
}

void RabbitSimulation::run(unsigned int week)
{
	for (unsigned int i = 0; i < week; ++i)
		grow();
}

unsigned int RabbitSimulation::get_childs_nb(std::list<Rabbit*> list)
{
	unsigned int i = 0;

	for (auto &&rabbit : list)
		if (rabbit->get_age() < rabbit->get_maturity())
			i++;
	
	return i;
}

unsigned int RabbitSimulation::get_childs_nb(std::list<RabbitFemale*> list)
{
	unsigned int i = 0;

	for (auto &&rabbit : list)
		if (rabbit->get_age() < rabbit->get_maturity())
			i++;
	
	return i;
}


void RabbitSimulation::grow()
{
	std::cout << "#" << _week << " : Nb males : " << _males.size() << '(' << get_childs_nb(_males) << ") ; Nb femelles : " << _females.size() << '(' << 
		get_childs_nb(_females) << ')' << std::endl;
	births();
	die();
	for (auto &&rabbit : _males)
		rabbit->grow();
	for (auto &&rabbit : _females)
		rabbit->grow();
	
	_week++;
}

void RabbitSimulation::births()
{
	if (!_males.empty())
		for (auto &&female : _females)
			female->give_birth(_week, _males, _females);
}

void RabbitSimulation::die()
{
	for (auto &&male : _males)
	{
		if (male->get_death_week() == _week)
		{
			delete male;
			male = nullptr;
		}
	}
	for (auto &&female : _females)
	{
		if (female->get_death_week() == _week)
		{
			delete female;
			female = nullptr;
		}
	}

	_males.remove(nullptr);
	_females.remove(nullptr);
}