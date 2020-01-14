#ifndef _BAVARDE_HPP_
#define _BAVARDE_HPP_

#include <iostream>

class Bavarde
{
public:
    Bavarde(int n = 0);
    ~Bavarde();
    int getN();
    void afficher();

private:
    int numero;
};

#endif // !_BAVARDE_HPP_