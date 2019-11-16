#include "RabbitFemale.hpp"

std::normal_distribution<> RabbitFemale::dist_birth(4.5, 9);
std::normal_distribution<> RabbitFemale::dist_nb_litters(6, 1);
std::uniform_int_distribution<short> RabbitFemale::dist_gender(1, 2); 
std::uniform_int_distribution<> RabbitFemale::dist_litters_dates(0, WEEK_PER_YEAR);

RabbitFemale::RabbitFemale():Rabbit()
{
	init_birth();
}
extern int c;
void RabbitFemale::init_birth()
{
	for (unsigned int i = _maturity_week - 4; i <= _death_week;)
	{
		unsigned short w = dist_birth(generator);
		i += w + GESTATION_DURATION;
		if (i <= _death_week)
			_weeks_of_birth[i] = dist_gender(generator);
	}

}