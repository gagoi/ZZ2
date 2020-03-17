#ifndef __CPP3_PRODUCTEUR_PREMIERS_HPP__
#define __CPP3_PRODUCTEUR_PREMIERS__HPP__

#include <iostream>
#include "producteur.hpp"
#include <string>

class ProducteurPremiersEntiers : public Producteur {
	public:
		virtual bool produire(int, std::string);
};

#endif
