//
// Created by joe on 07/10/16.
//

#include "Operation.hpp"

Operation::Operation() {

}

Operation::Operation(int numMachine, int numJob, int duree) : numMachine(numMachine), numJob(numJob), duree(duree) {

}

void Operation::affiche(std::ostream &flux) const {
    flux << "le job " << numJob << " se trouve sur la machine " << numMachine << " et dure " << duree << std::endl;

}

const std::ostream &operator<<(std::ostream &flux, const Operation &ope) {
    ope.affiche(flux);
    return flux;
}

int Operation::getNumMachine() const {
    return numMachine;
}

int Operation::getNumJob() const {
    return numJob;
}

int Operation::getDuree() const {
    return duree;
}
