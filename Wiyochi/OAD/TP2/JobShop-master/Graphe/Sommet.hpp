//
// Created by joe on 23/09/16.
//

#ifndef TP1_SOMMET_HPP
#define TP1_SOMMET_HPP


#include "Arc.hpp"
#include <vector>
#include <ostream>
#include <limits>

class Sommet {
    static int compte;
    int id ;
    float x, y;
    std::vector<Arc> adjacence;
public:

    double label = std::numeric_limits<double>::max(); // plus petite distante pour aller de o au Sommet
    bool mark = false;
    int prec ;


    Sommet();
    Sommet(int id, int x,int y);
    void setId(int id);
    void setX(float x);
    void setY(float y);
    const int getId() const;
    const float getX() const;
    const float getY() const;
    const std::vector<Arc> &getAdjacence() const;
    const Arc operator[](int id)const ;
    const int getNbVoisin();
    void affiche(std::ostream &flux) const ;
    void addArc(const Arc & arc);
};
std::ostream &operator<< (std::ostream & , const Sommet & sommet);

#endif //TP1_SOMMET_HPP
