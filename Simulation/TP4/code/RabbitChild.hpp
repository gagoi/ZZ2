#ifndef RABBITCHILD_HPP_
#define RABBITCHILD_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "Rabbit.hpp"

class RabbitChild : public Rabbit
{
private:
	const unsigned short _age_of_maturity;	// Age auquel le lapinou deviendra un lapin fort et musclé
public:
	RabbitChild();
};

#endif
