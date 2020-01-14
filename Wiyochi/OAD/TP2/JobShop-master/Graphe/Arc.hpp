//
// Created by joe on 23/09/16.
//

#ifndef TP1_ARC_HPP
#define TP1_ARC_HPP


#include <iosfwd>

class Arc {
    static int compte;
    int id;
    int origine;
    int destination;
    float cout;

public:
    Arc(int id, int origine, int destination, int poids);

    const int getId();

    const int getOrigine() const;

    const int getDestination() const;

    const float getCout() const;

    void setOrigine(int origine);

    void setDestination(int destination);

    void setCout(float cout);
    void afficher(std::ostream &flux) const ;


};
std::ostream & operator<<(std::ostream &, const Arc & arc);



#endif //TP1_ARC_HPP
