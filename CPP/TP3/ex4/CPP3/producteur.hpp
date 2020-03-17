#ifndef __CPP3_PRODUCTEUR_HPP__
#define __CPP3_PRODUCTEUR_HPP__

#include <iostream>
#include <string>

class Producteur {
	protected:
		int travail;
	public:
		Producteur();
		virtual bool produire(int, std::string) = 0;
		int getTravail();
};

#endif
