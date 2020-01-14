//
// Created by joe on 23/09/16.
//

#ifndef TP1_GRAPHE_HPP
#define TP1_GRAPHE_HPP


#include "Sommet.hpp"

class Graphe {
    std::string name;
    std::vector <Sommet> sommet;

    Sommet & getPlusPetitLabel() ;
public:
    Graphe(const std::string &fileName);
    const Sommet& operator[](int id);
    void afficher(std::ostream & flux) const ;
    void deijkstra();
    bool tousMarque();
    std::vector<int> createPath(int dest);



};

std::ostream & operator<< (std::ostream & flux, const Graphe &graphe);
#endif //TP1_GRAPHE_HPP
