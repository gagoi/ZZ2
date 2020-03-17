#ifndef GROUPE_HPP__
#define GROUPE_HPP__

#include <iostream>
#include <cstring>
#include <vector>

#include "Forme.hpp"

class Groupe : public Forme
{
	private:
		std::vector<Forme*> _formes;
	public:
		Groupe();
		Groupe(Groupe& g);
		virtual ~Groupe();
		void ajouterForme(Forme&);
		void afficher();
		virtual std::string toString() const;
		virtual Groupe* clone() const;
};
#endif