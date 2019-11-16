#include "RabbitFemale.hpp"

std::normal_distribution<> RabbitFemale::dist_birth(4.5, 9);
std::normal_distribution<> RabbitFemale::dist_nb_litters(6, 1);
std::uniform_int_distribution<short> RabbitFemale::dist_gender(1, 2); 
std::uniform_int_distribution<> RabbitFemale::dist_litters_dates(0, WEEK_PER_YEAR);

RabbitFemale::RabbitFemale(unsigned int week_offset):Rabbit(week_offset)
{
	init_birth();
}

RabbitFemale::~RabbitFemale()
{
	while (!litters.empty())
	{
		delete litters.front();
		litters.pop();
	}
}

void RabbitFemale::init_birth()
{
	for (unsigned int i = _maturity_week - 4; i <= _death_week;)
	{
		unsigned short w = dist_birth(generator);
		i += w + GESTATION_DURATION;
		if (i <= _death_week)
		{
			litter * l = new litter;
			l->males = 0;
			l->females = 0;
			l->week = i + _week_offset;
			short nb_baby= dist_nb_litters(generator);
			for (short i = 0; i < nb_baby; i++)
				if (dist_gender(generator) == 1)
					(l->males)++;
				else 
					(l->females)++;
			litters.push(l);
		}
	}
}

void RabbitFemale::give_birth(unsigned int week, std::list<Rabbit*>& males, std::list<RabbitFemale*>& females)
{
	if (!litters.empty() && litters.front()->week == week)
	{
		for (short i = 0; i < litters.front()->males; i++)
			males.push_back(new Rabbit(week));
		for (short i = 0; i < litters.front()->females; i++)
			females.push_back(new RabbitFemale(week));
		
		delete litters.front();
		litters.pop();
	}
}