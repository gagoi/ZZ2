//
// Created by lysilia on 07/10/16.
//

#include "Data.h"



#include <stdlib.h>
#include <algorithm>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>


Data::Data(){}
Data::~Data(){}


Data::Data(const std::string &fileName):nom(fileName){
    std::ifstream file (fileName.c_str());

    if(!file.is_open()){
        throw std::runtime_error(" impossible d'ouvrir le fichier");
    }

    // lecture de la premiere ligne (qui ne nous interesse pas)
    // pour pouvoir passer a la suivante
    std::string firstLine;
    getline(file, firstLine);

    // lecture des dimensions
    file >> nbOp >> nbEtape;

    // init de la matrice : taille fixe
    matriceOP.resize(nbOp);


    // creation de la matrice du graphe
    int numMachine, duree;

    for(int i = 0 ; i < nbOp ; ++i){
        matriceOP[i].resize(nbEtape);

        for(int j = 0 ; j < nbEtape ; ++j){
            file >> numMachine >> duree;
            matriceOP[i][j] = Operation(numMachine, i, duree);
        }
    }

    file.close();
}

int Data::getNbOp() const{
    return nbOp;
}

int Data::getNbEtape() const{
    return nbEtape;
}

std::vector<std::vector<Operation>>& Data::getMatreiceOp() {
    return matriceOP;
}


void Data::toString(std::ostream &flux) const{
    for(int i = 0 ; i < matriceOP.size() ; ++i)
        for(int j = 0 ; j < matriceOP[j].size() ; ++j)
            flux << matriceOP[i][j];
}

const std::ostream & operator<<(std::ostream &flux, const Data &data){
    data.toString(flux);
    return flux;
}

std::vector<Operation>& Data::getVectorOp(int index){
    return matriceOP[index];
}

const Operation& Data::getOperation(int i, int j)const{
    return matriceOP[i][j];
}

std::vector<Operation>& Data::operator[](int index){
    return matriceOP[index];
}