//
// Created by lysilia on 07/10/16.
//

#ifndef JOBSHOP_DATA_H
#define JOBSHOP_DATA_H


#include <string>
#include <vector>
#include <iostream>
#include "Operation.hpp"


class Data {
private:


    std::vector<std::vector<Operation>> matriceOP;
    int nbOp;
    int nbEtape;    // = nb de machine

public:
    std::string nom;
    Data();
    Data(const std::string &fileName);
    ~Data();

    int getNbOp() const;
    int getNbEtape() const;
     std::vector<std::vector<Operation>>& getMatreiceOp();

    std::vector<Operation>& getVectorOp(int index);
    const Operation& getOperation(int i, int j)const;
    std::vector<Operation>& operator[](int index);
    void toString(std::ostream &flux) const;


};


const std::ostream & operator<<(std::ostream &flux, const Data &data);


#endif //JOBSHOP_DATA_H
