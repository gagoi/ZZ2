//
// Created by joe on 23/09/16.
//

#include "Arc.hpp"
#include <iostream>
int Arc::compte = 0;

Arc::Arc(int id, int origine, int destination, int poids) : origine(origine), destination(destination), id(id), cout(poids){

}

const int Arc::getId() {
    return id;
}

const int Arc::getOrigine() const {
    return origine;
}

const int Arc::getDestination() const {
    return destination;
}

const float Arc::getCout() const {
    return cout;
}


void Arc::setOrigine(int origine) {
    Arc::origine = origine;
}

void Arc::setDestination(int destination) {
    Arc::destination = destination;
}

void Arc::setCout(float cout) {
    Arc::cout = cout;
}

void Arc::afficher(std::ostream &flux) const  {
    flux << "arc de " << origine << " à " << destination ;

}

std::ostream &operator<<(std::ostream &flux, const Arc &arc) {
    arc.afficher(flux);
    return flux;
}
