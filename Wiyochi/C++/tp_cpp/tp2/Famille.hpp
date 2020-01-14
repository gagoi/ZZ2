#ifndef _FAMILLE_HPP_
#define _FAMILLE_HPP_

#include "Bavarde.hpp"

class Famille
{
public:
    Famille(unsigned int taille);
    ~Famille();

private:
    Bavarde* set;
};

#endif // !_FAMILLE_HPP_