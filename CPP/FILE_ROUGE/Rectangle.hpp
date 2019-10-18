#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <string>

#include "Forme.hpp"

enum TYPE {
	SIZE,
	COORD
};

class Rectangle : public Forme
{
	public:
		Rectangle(int x = 0, int y = 0, int w = 0, int h = 0, int type = SIZE);
		virtual std::string toString() const;

};


#endif