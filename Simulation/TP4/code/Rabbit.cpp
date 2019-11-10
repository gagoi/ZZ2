#include "Rabbit.hpp"

std::random_device Rabbit::_rand_device = std::random_device();
std::mt19937 Rabbit::_generator = std::mt19937(_rand_device());
std::normal_distribution<int> Rabbit::_normal_distrib = std::normal_distribution(6, 1);

Rabbit::Rabbit():
	_age(0), _mortatility(0.5)
{
}
