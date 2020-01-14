#ifndef _CERCLE_HPP_
#define _CERCLE_HPP_

#include <iostream>
#include <string>
#include "Forme.hpp"

class Cercle : public Forme
{
public:
    Cercle();
    Cercle(int x, int y, int w, int h);
    Cercle(int x, int y, int rayon);
    void setRayon(int r);
    int getRayon() const;
    std::string toString() const;
    Cercle* clone() const;
};

#endif // !_CERCLE_HPP_