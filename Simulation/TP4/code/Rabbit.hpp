#ifndef RABBIT_HPP_
#define RABBIT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <array>

class Rabbit
{
protected:
	static constexpr unsigned short WEEK_PER_YEAR = 52;
	static constexpr unsigned int MAX_LIFESPAN = 15 * WEEK_PER_YEAR; // Durée de vie max en semaine
	static constexpr unsigned int MATURITY_MIN = 4 * 4; // Age en semaine à partir duquel un lapin peut devenir mature
	static constexpr unsigned int MATURITY_MAX = 8 * 4; // Age en semaine jusqu'auquel un lapin peut devenir mature

private:
	unsigned int _age;	// Age en semaine
	static std::array<double,3> intervals;
	static std::array<double,3> weights;
	
	unsigned int init_death();

protected:
	static std::random_device rand_device;
	static std::mt19937 generator;
	static std::uniform_real_distribution<> unifor_real_distribution;
	static std::uniform_int_distribution<> dist_maturity;
	static std::geometric_distribution<int> dist_maturity_death;
	static std::geometric_distribution<int> dist_baby_death;
	static std::piecewise_linear_distribution<double> dist_death_end;

	unsigned int _maturity_week; // Age en semaine auquel le lapin sera mature
	unsigned int _death_week; // Age en semaine auquel le lapin va mourir

	public:
	Rabbit();
	int grow();

	inline unsigned int get_death_week() {return _death_week;};
};

#endif
