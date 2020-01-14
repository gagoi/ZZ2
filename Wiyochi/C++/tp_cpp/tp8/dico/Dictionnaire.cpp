#include "Dictionnaire.hpp"

Dictionnaire::Dictionnaire()
{
}

Dictionnaire::~Dictionnaire()
{
}

void Dictionnaire::ajouterMot(std::string const & inMot)
{
    std::map<char, ListeMotsTries>::iterator it = _dico.find(inMot[0]);
    if (it != _dico.end())
    {
        (*it).second.ajouterMot(inMot);
    }
}

void Dictionnaire::retirerMot(std::string const & inMot)
{
    std::map<char, ListeMotsTries>::iterator it = _dico.find(inMot[0]);
    if (it != _dico.end())
    {
        (*it).second.retirerMot(inMot);
    }
}

int Dictionnaire::getNbMots() const
{
    int t = 0;
    std::for_each(_dico.begin(), _dico.end(),
    [&](std::pair<char, ListeMotsTries>& p)
    {
        t++;
    });
    return t;
}

ListeMotsTries& Dictionnaire::rechercherMots(std::string const & inMot)
{
    ListeMotsTries str_lettre = (*_dico.find(inMot[0])).second;

    ListeMotsTries liste;

}
