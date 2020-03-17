#ifndef __CPP3_PRODUCTEUR_ALEA_HPP__
#define __CPP3_PRODUCTEUR_ALEA_HPP__

#include <iostream>
#include <string>
#include <cstdlib>
#include "producteur.hpp"

class ProducteurAleatoire : public Producteur {
	public:
		virtual bool produire(int, std::string);
};

#endif
