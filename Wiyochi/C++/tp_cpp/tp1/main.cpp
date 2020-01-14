#include <iostream>
#include "Point.hpp"

void fct1(int a)
{
    std::cout << &a << std::endl;
}

void fct2(int& a)
{
    std::cout << &a << std::endl;
}

void echangePtr(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void echangeRef(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

void mainPoint()
{
    Point p1;
    Point p2(10, 5);
    Point p3(0, 0);
    Point* p4 = new Point(10, 5);

    // std::cout << p1.x << std::endl; <- impossible, x est un attribut privé

    std::cout << p1 << p2 << p3 << *p4 << std::endl;
    std::cout << Point::nombreDePoints() << std::endl;
    std::cout << p1.nombreDePoints() << std::endl;

    delete p4;
}

void mainReference()
{
    int age = 41;
    int a = 10;
    int b = 5;

    std::cout << &age << std::endl;
    fct1(age);
    fct2(age);

    std::cout << "a: " << a << ", b: " << b << std::endl;
    echangePtr(&a, &b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
    echangeRef(a, b);
    std::cout << "a: " << a << ", b: " << b << std::endl;
}

void mainAlloc()
{
    int * p = new int;
    *p = 3;
    std::cout << *p << std::endl;
    delete p;

    const int taille = 500;

    int * tab = new int[taille];

    for(auto i = 0; i < taille; ++i) tab[i] = i;
    for(auto i = 0; i < taille; ++i) std::cout << tab[i] << std::endl;

    delete[] tab;
}

int main(int, char**)
{
    //mainPoint();
    //mainReference();
    mainAlloc();

    return 0;
}