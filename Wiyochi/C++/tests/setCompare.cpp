#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>

class Point
{
public:
    int x;
    int y;

    Point(int a, int b) : x(a), y(b) {}
    ~Point() {}
};

struct Compare
{
    bool operator()(Point const & c1, Point const & c2) {
        return sqrt(c1.x * c1.x + c1.y * c1.y) < sqrt(c2.x * c2.x + c2.y * c2.y);
    }

    bool operator()(Point* const & c1, Point* const & c2) {
        return sqrt(c1->x * c1->x + c1->y * c1->y) < sqrt(c2->x * c2->x + c2->y * c2->y);
    }
};


int main()
{
    std::set<Point, Compare> setOfPoints;

    setOfPoints.insert(Point(5, 2));
    setOfPoints.insert(Point(0, 0));
    setOfPoints.insert(Point(10, 10));
    setOfPoints.insert(Point(0, 0));
    setOfPoints.insert(Point(-1, -1));

    std::for_each(setOfPoints.begin(), setOfPoints.end(), [](Point const& p)
    {
        std::cout << "[" << p.x << "," << p.y << "]" << std::endl;
    });

    std::cout << std::endl;

    std::set<Point*, Compare> setOfPtr;

    setOfPtr.insert(new Point(5, 2));
    setOfPtr.insert(new Point(0, 0));
    setOfPtr.insert(new Point(10, 10));
    setOfPtr.insert(new Point(0, 0)); // Perdu -> fuite de mémoire (à cause de set =/= multiset)
    setOfPtr.insert(new Point(-1, -1));

    std::for_each(setOfPtr.begin(), setOfPtr.end(), [](Point* const& p)
    {
        std::cout << "[" << p->x << "," << p->y << "]" << std::endl;
        delete p;
    });
    

    return 0;
}