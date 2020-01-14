#ifndef GROUPE_HPP_
#define GROUPE_HPP_

#include <string>
#include <vector>
#include <sstream>
#include "Forme.hpp"

class Groupe : public Forme
{
public:
    Groupe();
    ~Groupe();
    void ajouter(Forme* nForme);

    std::string toString() const;
    Groupe* clone() const;

private:
    std::vector<Forme*> _list;
};

#endif