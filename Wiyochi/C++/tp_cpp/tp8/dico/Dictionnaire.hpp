#ifndef DICO_HPP
#define DICO_HPP

#include <map>
#include <string>
#include "ListeMotsTries.hpp"

class Dictionnaire
{
public:
    Dictionnaire();
    ~Dictionnaire();

    void ajouterMot(std::string const & inMot);
    void retirerMot(std::string const & inMot);
    int getNbMots() const;
    ListeMotsTries& rechercherMots(std::string const & inMot);

private:
    std::map<char, ListeMotsTries> _dico;
};

#endif