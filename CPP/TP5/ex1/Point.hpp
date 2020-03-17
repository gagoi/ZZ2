#ifndef _POINT_H_
#define _POINT_H_

#include <string>
#include <sstream>
#include <iostream>


class Point
{
	private:
		int _x;
		int _y;
	public:
		Point(int x = 0, int y = 0);
		std::string toString() const;
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);

};

extern const Point ORIGINE;
#endif