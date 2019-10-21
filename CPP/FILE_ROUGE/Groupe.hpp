#ifndef GROUPE_HPP__
#define GROUPE_HPP__

#include <iostream>
#include <cstring>

#include "Forme.hpp"

constexpr static int size = 40;

class Groupe : public Forme
{
	private:
		unsigned int _nbFormes;
		Forme* _formes[size];
	public:
		Groupe();
		Groupe(Groupe& g);
		void ajouterForme(Forme&);
		void afficher();
		virtual std::string toString() const;
		virtual Groupe* clone() const;
		~Groupe();
};
#endif