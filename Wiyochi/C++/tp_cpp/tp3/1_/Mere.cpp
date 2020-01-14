#include "Mere.hpp"

int Mere::n_mere = 0;

Mere::Mere()
{
    n_mere++;
    std::cout << "nombre de meres: " << n_mere << std::endl;
}

Mere::Mere(std::string n) :
    nom(n)
{
}

Mere::~Mere()
{
}

std::string Mere::getNom()
{
    return nom;
}

void Mere::afficher()
{
    std::cout << "Classe Mere" << std::endl;
}

int Mere::getNbMere()
{
    return n_mere;
}