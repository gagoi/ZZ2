#include "B.hpp"
#include "A.hpp"

B::B() : j(0)
{
}

B::~B()
{
}

void B::send(A& a)
{
    a.exec(3);
}

void B::exec(int n)
{
    j += n;
}

void B::afficher()
{
    std::cout << j << std::endl;
}