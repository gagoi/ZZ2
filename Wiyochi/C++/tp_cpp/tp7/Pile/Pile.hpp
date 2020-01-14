#ifndef PILE_GEN_HPP_
#define PILE_GEN_HPP_

#include <iostream>
#include <string>
#include <exception>

const int DEFAULT_SIZE = 10;

template<typename T>
class Pile
{
public:
    Pile();
    Pile(int s);
    Pile(const Pile<T>& o);
    ~Pile();

    Pile<T>& operator=(const Pile<T>& o);
    bool empty() const;
    void push(T elem);
    void pop();
    int top() const;
    int size() const;

private:
    T* _tab;
    int _max_size;
    int _size;
};

#include "Pile.tpp"

#endif // !PILE_HPP_