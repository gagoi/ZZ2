#ifndef POINT_HPP_
#define POINT_HPP_

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

private:
	int _x;
	int _y;
};

extern Point ORIGINE;

#endif
