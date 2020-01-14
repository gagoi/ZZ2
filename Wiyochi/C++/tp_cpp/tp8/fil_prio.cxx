#include <vector>
#include <queue>
#include <string>
#include <iostream>

class ZZ {
public:
    ZZ(std::string const & na, std::string const & p, double n) :
        nom(na), prenom(p), note(n) {}

    friend std::ostream& operator<<(std::ostream& out, ZZ const& z)
    {
        out << z.nom << " " << z.prenom << " : " << z.note;
        return out;
    }

    friend bool operator<(ZZ const & o1, ZZ const & o2)
    {
        return o1.note < o2.note;
    }

private:
    std::string nom, prenom;
    double note;
};



int main()
{
    using vzz = std::vector<ZZ> ;

    vzz zz;

    zz.push_back(ZZ("et2", "preEt1", 10.0));
    zz.push_back(ZZ("et1", "preEt1", 1.0));
    zz.push_back(ZZ("et4", "preEt1", 20.0));
    zz.push_back(ZZ("et3", "preEt1", 11.0));

    std::priority_queue<ZZ> tri;

    for(vzz::iterator it = zz.begin(); 
        it!=zz.end(); ++it)
    tri.push(*it);

    while(!tri.empty()) {
        std::cout << tri.top() << std::endl;
        tri.pop();
    }
    return 0;
}