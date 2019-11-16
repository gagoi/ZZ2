#include "Rabbit.hpp"

std::array<double, 3>  Rabbit::intervals{14 * WEEK_PER_YEAR, 14 * WEEK_PER_YEAR, MAX_LIFESPAN};
std::array<double, 3> Rabbit::weights {0, 0, 1};

std::mt19937 Rabbit::generator(8);
std::uniform_real_distribution<double> Rabbit::unifor_real_distribution(0, 1);
std::uniform_int_distribution<> Rabbit::dist_maturity(MATURITY_MIN, MATURITY_MAX);
std::geometric_distribution<int> Rabbit::dist_baby_death(0.1);
std::geometric_distribution<int> Rabbit::dist_maturity_death(0.003);

std::piecewise_linear_distribution<double> Rabbit::dist_death_end(Rabbit::intervals.begin(),Rabbit::intervals.end(),Rabbit::weights.begin());



Rabbit::Rabbit():
	_age(0), _maturity_week(dist_maturity(generator)), _death_week(init_death())
{
}

unsigned int Rabbit::init_death()
{
	constexpr double _mortality_before_maturity = 0.8;
	constexpr double _mortality_before_increments = 0.5;

	unsigned int death_week = 0;

	if (unifor_real_distribution(generator) < _mortality_before_maturity)
		do
		{
			death_week = dist_baby_death(generator);
		}	
		while(death_week > _maturity_week);
	else if (unifor_real_distribution(generator) < _mortality_before_increments)
		do
		{
			death_week = dist_maturity_death(generator) + _maturity_week;
		} while (death_week > 14 * WEEK_PER_YEAR);
		
	else 
	{
		death_week = dist_death_end(generator);
	}

	return death_week;
}
