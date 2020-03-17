#ifndef __CPP3_STATISTICIEN_HPP__
#define __CPP3_STATISTICIEN_HPP__

#include <iostream>
#include <fstream>

class Statisticien {
	private:
		bool calcul;
		int _somme;
	public:
		Statisticien();
		void acquerir(std::string);
		bool aCalcule();
		int somme();

};

#endif