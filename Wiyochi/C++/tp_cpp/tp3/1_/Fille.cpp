#include "Fille.hpp"

Fille::Fille() :
    Mere()
{
    std::cout << "Constructeur de fille" << std::endl;
}

Fille::Fille(std::string n) :
    Mere(n)
{
}

Fille::~Fille()
{
}

void Fille::testAtt()
{
    std::cout << "public: " << att_public << std::endl;
    std::cout << "protected: " << att_prot << std::endl;
    // std::cout << "private: " << att_priv << std::endl; -> ne fonctionne pas, on ne peut pas acceder a un attriibut privé de la classe mere
}

void Fille::afficher()
{
    std::cout << "Classe Fille" << std::endl;
}