#include <iostream>
#include "A.hpp"
#include "B.hpp"

int main()
{
    A a;
    B b;

    a.send(b);

    a.afficher();
    b.afficher();

    return 0;
}