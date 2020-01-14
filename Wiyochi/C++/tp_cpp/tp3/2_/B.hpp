#ifndef _B_HPP
#define _B_HPP

#include <iostream>

class A /*{
    public: void exec(int n);
}*/;

class B
{
public:
    B();
    ~B();
    void send(A& a);
    void exec(int n);
    void afficher();

private:
    int j;
};

#endif // !_B_HPP