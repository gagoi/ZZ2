#include "ListeMotsTries.hpp"

ListeMotsTries::ListeMotsTries()
{
}

ListeMotsTries::~ListeMotsTries()
{
}

void ListeMotsTries::ajouterMot(std::string const & inMot)
{
    _list.push_back(inMot);
    _list.sort();
}

void ListeMotsTries::retirerMot(std::string const & inMot)
{
    _list.remove(inMot);
}

void ListeMotsTries::inserer(const_iterator const & inDebut, const_iterator const & inFin)
{
    for (const_iterator it = inDebut; it != inFin; it++)
    {
        _list.push_back(*it);
    }
    _list.sort();
}

int  ListeMotsTries::getNbMots() const
{
    return _list.size();
}

void ListeMotsTries::afficher(std::ostream & out) const
{
    std::copy(debut(), fin(), std::ostream_iterator<std::string>(out, "\n"));
}

ListeMotsTries::const_iterator ListeMotsTries::debut() const
{
    return _list.cbegin();
}

ListeMotsTries::const_iterator ListeMotsTries::fin() const
{
    return _list.cend();
}

std::ostream& operator<<(std::ostream& out, ListeMotsTries const & l)
{
    l.afficher(out);
    return out;
}