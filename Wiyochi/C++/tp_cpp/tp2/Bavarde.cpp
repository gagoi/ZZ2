#include "Bavarde.hpp"

Bavarde::Bavarde(int n) :
    numero(n)
{
    std::cout << "Construction de " << numero << std::endl;
}

Bavarde::~Bavarde()
{
    std::cout << "Tais-toi " << numero << std::endl;
}

int Bavarde::getN()
{
    return numero;
}

void Bavarde::afficher()
{
    std::cout << "Affichage de " << numero << std::endl;
}