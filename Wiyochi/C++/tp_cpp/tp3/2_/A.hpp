#ifndef _A_HPP
#define _A_HPP

#include <iostream>

class B;

class A
{
public:
    A();
    ~A();
    void send(B& b) const;
    void exec(int n);
    void afficher();

private:
    int i;
};

#endif // !_A_HPP