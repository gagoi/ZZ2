//
// Created by joe on 23/09/16.
//

#include <iostream>
#include "Sommet.hpp"

int Sommet::compte = 0;

Sommet::Sommet() : x(0), y(0), id(compte++){

}

Sommet::Sommet(int id, int x, int y):id(id), x(x), y(y) {

}

const float Sommet::getX() const {
    return x;
}

const float Sommet::getY() const {
    return y;
}

const int Sommet::getId() const {
    return id;
}

const std::vector<Arc> &Sommet::getAdjacence() const {
    return adjacence;
}

void Sommet::setId(int idNew) {
    id = idNew;
}

void Sommet::setX(float xNew) {
    x = xNew;
}

void Sommet::setY(float yNew) {
    y = yNew;
}

const Arc Sommet::operator[](int id) const {
    return adjacence[id];
}

const int Sommet::getNbVoisin() {
    return adjacence.size();
}

void Sommet::affiche(std::ostream &flux) const  {
    flux << id <<" "<< std::endl;
    for (int i = 0; i < adjacence.size(); i++){
        std::cout << adjacence[i] << std::endl;
    }


}

std::ostream &operator<<(std::ostream &flux, const Sommet &sommet) {

    sommet.affiche(flux);
    return flux;

}

void Sommet::addArc(const Arc &arc) {
    adjacence.push_back(arc);

}
