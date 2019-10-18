#include "Mere.hpp"

int Mere::cpt = 0;

Mere::Mere(int id, std::string nom):
	_id(id), _nom(nom)
{
	cpt++;
	std::cout << "Construction de " << _nom << " : " << id << " ---- " << cpt << std::endl;
}

Mere::~Mere()
{
	std::cout << "Destruction de : " << _id << std::endl;
}

int Mere::getCpt()
{
	return cpt;
}

std::string Mere::getNom()
{
	return _nom;
}

void Mere::afficher()
{
	std::cout << "JE SUIS UNE MERE" << std::endl;
}