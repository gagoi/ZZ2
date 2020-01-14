#include "A.hpp"
#include "B.hpp"

A::A() : i(0)
{
}

A::~A()
{
}

void A::send(B& b) const
{
    b.exec(3);
}

void A::exec(int n)
{
    i += n;
}

void A::afficher()
{
    std::cout << i << std::endl;
}