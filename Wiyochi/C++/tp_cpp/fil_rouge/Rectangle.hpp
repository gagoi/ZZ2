#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include <iostream>
#include <string>
#include "Forme.hpp"

class Rectangle : public Forme
{
public:
    Rectangle();
    Rectangle(int x, int y, int w, int h);
    std::string toString() const;
    Rectangle * clone() const;
};

#endif // !_RECTANGLE_HPP_