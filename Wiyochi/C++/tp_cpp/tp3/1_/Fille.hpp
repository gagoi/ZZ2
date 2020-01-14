#ifndef _FILLE_HPP_
#define _FILLE_HPP_

#include <iostream>
#include <string>
#include "Mere.hpp"

class Fille : public Mere
{
public:
    Fille();
    Fille(std::string n);
    ~Fille();
    void testAtt();
    void afficher();
};

#endif // !_FILLE_HPP_