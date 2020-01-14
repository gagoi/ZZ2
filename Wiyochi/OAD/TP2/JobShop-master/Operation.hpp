//
// Created by joe on 07/10/16.
//

#ifndef JOBSHOP_OPERATION_HPP
#define JOBSHOP_OPERATION_HPP


#include <ostream>

class Operation {

    int numMachine ;
    int numJob;
    int duree;

public:
    Operation();
    Operation(int numMachine, int numJob, int duree);
    void affiche(std::ostream & flux)const;

    int getNumMachine() const;

    int getNumJob() const;

    int getDuree() const;


};

const std::ostream & operator<<(std::ostream &flux, const Operation & ope);


#endif //JOBSHOP_OPERATION_HPP
