#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <iostream>

class Point
{
private:
    int x;
    int y;

    static int compteur;
    
public:
    Point();
    Point(int nX, int nY);
    ~Point();

    int getX();
    void setX(int nX);
    int getY();
    void setY(int nY);
    void deplacerDe(int dX, int dY);
    void deplacerVers(int nX, int nY);

    static int nombreDePoints();

    friend std::ostream& operator<<(std::ostream& out, Point& p);
};

#endif // !_POINT_HPP_