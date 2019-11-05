#ifndef RABBIT_HPP_
#define RABBIT_HPP_

#include <iostream>
#include <string>
#include <vector>

class Rabbit
{
private:
	unsigned int _age;	// Age en semaine
	float _mortatility;	// Chance de mort du lapin
public:
	Rabbit();
	int grow();
};

#endif
