#include "Groupe.hpp"

Groupe::Groupe() :
    Forme()
{
}

Groupe::~Groupe()
{
}

std::string Groupe::toString() const
{
    std::ostringstream oss;
    oss << "GROUPE " << getId() << "(" << _origin.getX() << "," << _origin.getY() << "," << _width << "," << _height << ")";
    if (_list.size() > 0)
    {
        oss << std::endl;
        std::vector<Forme*>::const_iterator it;
        for (it = _list.cbegin(); it < _list.end() - 1; it++)
            oss << "  " << (*it)->toString() << std::endl;
        oss << "  " << (*it)->toString(); // Pour ne pas afficher le dernier std::endl
    }

    return oss.str();
}

void Groupe::ajouter(Forme* nForme)
{
    _list.push_back(nForme);

    int xForme = nForme->getPoint().getX();
    int yForme = nForme->getPoint().getY();

    if (_list.size() == 1)
    {
        getPoint().setX(xForme);
        getPoint().setY(yForme);
        setLargeur(nForme->getLargeur());
        setHauteur(nForme->getHauteur());
    }
    else
    {
        if (xForme < getPoint().getX())
            getPoint().setX(xForme);
        if (yForme < getPoint().getY())
            getPoint().setY(yForme);

        if (xForme + nForme->getLargeur() > getPoint().getX() + getLargeur())
            setLargeur(nForme->getLargeur() + xForme - getPoint().getX());
        if (yForme + nForme->getHauteur() > getPoint().getY() + getHauteur())
            setHauteur(nForme->getHauteur() + yForme - getPoint().getY());
    }
}

Groupe* Groupe::clone() const
{
    return new Groupe(*this);
}