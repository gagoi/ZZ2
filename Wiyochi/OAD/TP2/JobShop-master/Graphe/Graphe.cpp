//
// Created by joe on 23/09/16.
//

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Graphe.hpp"

Graphe::Graphe(const std::string &fileName) :name(fileName){

    std::ifstream file (fileName.c_str());
    if(!file.is_open()){
        std::cerr << "erreur : impossible d'ouvrir " << fileName << std::endl;
        exit(1);
    }
    // lit les dimensions
    int n, m;
    file >> n >> m;
    //lit les sommets
    for(int i = 0; i < n; i++){
        int id, x, y;
        file >> id >> x >> y;
        sommet.push_back(Sommet(id, x, y));
    }
    sommet[0].label = 0;
    for (int i = 0; i < m; i++){
        int id, origin, dest, poids;
        file >> id >> origin >> dest >> poids;
        sommet[origin].addArc(Arc(id, origin, dest, poids));
    }

}




const Sommet& Graphe::operator[](int id) {
    int renvoie;
    for (int i = 0; i< sommet.size(); i++){
        if((renvoie = sommet[i].getId()) == id){
            break;
        }
    }
    return sommet[id];
}

void Graphe::afficher(std::ostream &flux) const {
    for (int i = 0 ; i < sommet.size() ; i++){
        flux << sommet[i];
    }

}

void Graphe::deijkstra() {
    auto comp = [](const Sommet &a, const Sommet& b){
        return a.label < b.label;
    };
  /*  std::make_heap(sommet.begin(), sommet.end(), comp);
    auto i = sommet.end();*/
    while(!tousMarque() ){
       /* std::pop_heap(sommet.begin(),  i--, comp);
        Sommet &temp = sommet.back();
        temp.mark = true;
        for(auto & arc: temp.getAdjacence()){

        }*/
        Sommet &temp = getPlusPetitLabel();

        for(auto & arc: temp.getAdjacence()){
            if(sommet[arc.getDestination()].label > temp.label + arc.getCout()){
                sommet[arc.getDestination()].label = temp.label + arc.getCout();
                temp.prec = arc.getDestination();
            }
        }
    }


}

bool Graphe::tousMarque() {
    for(auto & s : sommet){
        if(!s.mark)
            return  false;
    }
    return  true;
}

std::ostream &operator<<(std::ostream &flux, const Graphe &graphe) {
    graphe.afficher(flux);
    return flux;
}

Sommet& Graphe::getPlusPetitLabel()  {
    double petit = std::numeric_limits<double>::max();
    int j = 0;
    for(int i = 0; i < sommet.size(); i++){
        if(sommet[i].label < petit && !sommet[i].mark){
            petit = sommet[i].label;
            j = i;
        }
    }
    sommet[j].mark = true;
    return sommet[j];
}

std::vector<int> Graphe::createPath(int dest) {
    Sommet  temp ;
    std::vector<int> path;
    while(temp.label != 0){
        temp = sommet[dest];
        path.push_back(dest);
        dest = temp.prec;
    }
    std::reverse(path.begin(), path.end());
    return path;


}
