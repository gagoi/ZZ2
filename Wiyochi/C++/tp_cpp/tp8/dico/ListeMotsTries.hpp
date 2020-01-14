#ifndef LISTE_MOTS_HPP
#define LISTE_MOTS_HPP

#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

class ListeMotsTries
{
public:
    using iterator = std::list<std::string>::iterator;
    using const_iterator = std::list<std::string>::const_iterator;

    ListeMotsTries();
    ~ListeMotsTries();

    void ajouterMot(std::string const & inMot);
    void retirerMot(std::string const & inMot);
    void inserer(const_iterator const & inDebut, const_iterator const & inFin);
    int  getNbMots() const;
    void afficher(std::ostream & out = std::cout) const;
    const_iterator debut() const;
    const_iterator fin() const;

private:
    std::list<std::string> _list;
};

std::ostream& operator<<(std::ostream& out, ListeMotsTries const & l);

#endif