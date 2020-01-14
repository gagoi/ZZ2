#ifndef PILE_HPP_
#define PILE_HPP_

#include <iostream>
#include <string>
#include <exception>

const int DEFAULT_SIZE = 10;

class Pile
{
public:
    Pile();
    Pile(int s);
    Pile(const Pile& o);
    ~Pile();

    Pile& operator=(const Pile& o);
    bool empty() const;
    void push(int elem);
    void pop();
    int top() const;
    int size() const;

private:
    int* _tab;
    int _max_size;
    int _size;
};

#endif // !PILE_HPP_