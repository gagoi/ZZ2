#ifndef FILLE_H_
#define FILLE_H_

#include "Mere.hpp"

class Fille : public Mere
{
	public:
		Fille(int id = 0, std::string nom = "");
		~Fille();
		void afficher();
};

#endif