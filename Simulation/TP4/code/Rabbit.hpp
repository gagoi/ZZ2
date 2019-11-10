#ifndef RABBIT_HPP_
#define RABBIT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <random>

class Rabbit
{
private:
	unsigned int _age;	// Age en semaine
	float _mortatility;	// Chance de mort du 
protected:
	static std::random_device _rand_device;
	static std::mt19937 _generator;
	static std::normal_distribution<int> _normal_distrib;
	static constexpr size_t MAX_LIFESPAN = 15 * 52; // Durée de vie max en semaine
public:
	Rabbit();
	int grow();
};

#endif
