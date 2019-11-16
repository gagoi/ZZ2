#include "RabbitFemale.hpp"

std::normal_distribution<> RabbitFemale::dist_birth(4.5, 9);
std::normal_distribution<> RabbitFemale::dist_nb_litters(6, 1);
std::uniform_int_distribution<> RabbitFemale::dist_litters_dates(0, WEEK_PER_YEAR);

RabbitFemale::RabbitFemale():Rabbit()
{
	init_birth();
}
extern int c;
void RabbitFemale::init_birth()
{
	int cumul = 0;
	int bb = 0;
	for (unsigned int i = _maturity_week - 4; i <= _death_week;)
	{
		unsigned int old_i = i;
		unsigned short w = dist_birth(generator);
		i += w + GESTATION_DURATION;
		//std::cout << (i - old_i)/4 << std::endl;
		if (i <= _death_week)
		{
			_weeks_of_birth[i] = true;
			bb++;
				cumul += i - old_i;
				if (cumul > 52)
				{
					cumul = 0;
    	  		 	++hist[bb];
					if (bb > 8)
						c++;
					bb = 0;
			}
		}
	}

}