#include "Famille.hpp"

Famille::Famille(unsigned int taille)
{
    set = new Bavarde[taille];
}

Famille::~Famille()
{
    delete[] set;
}