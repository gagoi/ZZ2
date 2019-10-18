#include "Fille.hpp"

Fille::Fille(int id, std::string nom):Mere(id, nom)
{
	std::cout << "Construction fille : " << id << std::endl;
}

Fille::~Fille()
{
	std::cout << "Destruction fille : " << _id << std::endl;
}

void Fille::afficher()
{
	std::cout << "JE SUIS UNE FILLE" << std::endl;
}