#ifndef LISTE_HPP__
#define LISTE_HPP__

#include <iostream>

#include "Forme.hpp"

constexpr static int size = 40;

class Liste {
	private:
		unsigned int _nbFormes;
		Forme* _formes[size];
	public:
		Liste();
		void ajouterForme(Forme&);
		void afficher();
		~Liste();
};
#endif