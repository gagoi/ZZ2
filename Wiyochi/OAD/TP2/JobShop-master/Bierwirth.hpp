//
// Created by joe on 13/10/16.
//

#ifndef JOBSHOP_BIERWIRTH_HPP
#define JOBSHOP_BIERWIRTH_HPP

#include "Data.h"
#include <ostream>
#include<limits>
template <typename T>
using matrice = std::vector<std::vector<T>>;
class Bierwirth {
    struct dataLastMachine{
        int dateLiberation;
        std::pair<int, int> posMachine;     // job = ligne, etape = colonne dans la matrice dateDemarrage
        dataLastMachine():dateLiberation(0), posMachine(-1, -1){}
        dataLastMachine(int date, int job, int etape):dateLiberation(date), posMachine(job, etape){}
    };



    int nombreMachine;
    int nombreJob;
    std::vector<int> vectBierwirth;
    std::vector<int> lastJob;           // cf last op photo : date dispo
    std::vector<dataLastMachine> lastMachine;       // cf last job photo : duree occup
    int makespan = 0;       // derniere dateAuplusTOT de la matrice dateDemarrage


    struct chemin{
        int demarragePlusTot;
        std::pair<int, int> prec;
        chemin(int dem, int i, int j);
        chemin():demarragePlusTot(0), prec(-1, -1){}
    };



    matrice<chemin> dateDemarrage;

    void raz();
public:
    Bierwirth(int nombreMachine, int nombreJob);
    void shuffle();
    int evaluate(Data & data);
    void affiche(std::ostream & flux) const ;
    matrice<chemin> getDateDemarrage();
    int recupMakespan();
    int getBestMakespan(Data &data, int GRASP = 0);
    std::vector<int> swapVecteur(int index);

};
std::ostream & operator<< (std::ostream & flux, const Bierwirth & bierwirth);

#endif //JOBSHOP_BIERWIRTH_HPP
