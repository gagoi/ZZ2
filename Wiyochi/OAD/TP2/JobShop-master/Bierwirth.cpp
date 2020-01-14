//
// Created by joe on 13/10/16.
//

#include <algorithm>
#include "Bierwirth.hpp"
#include "Data.h"
#include "Operation.hpp"


Bierwirth::Bierwirth(int nombreMachine, int nombreJob) : nombreMachine(nombreMachine), nombreJob(nombreJob) {
    vectBierwirth.resize(nombreJob * nombreMachine);
    lastMachine.resize(nombreMachine);
    lastJob.resize(nombreJob);
    for (auto &l: lastJob) {
        l = -1;
    }
    dateDemarrage.resize(nombreJob);
    for (auto &date  :dateDemarrage) {
        date.resize(nombreMachine);
    }
    shuffle();
}

void Bierwirth::shuffle() {
    int index = 0;
    for (int i = 0; i < nombreJob; i++) {
        for (int j = 0; j < nombreMachine; j++) {
            vectBierwirth[index++] = i;
        }
    }
    for (int i = 0; i < 4; i++)
        std::random_shuffle(vectBierwirth.begin(), vectBierwirth.end());

}

Bierwirth::chemin::chemin(int dem, int i, int j) : demarragePlusTot(dem), prec(i, j) {}


/**
 * rempli une matrice de date au plus tot
 */
int Bierwirth::evaluate(Data &data) {
    auto &matriceOP = data.getMatreiceOp();
    int max;
    for (auto &itemVecBierwirth : vectBierwirth) {
        // etape de notre job
        int &jobEnCours = lastJob[itemVecBierwirth];
        jobEnCours++;

        // itemVecBierwirth : num job (ligne) dans le vecteur de bierwith (11122233) --> ligne matrice dateDemarrage
        // jobEnCours : num occurence du job    --> colonne matrice dateDemarrage

        Operation &operation = matriceOP[itemVecBierwirth][jobEnCours];

        int numMachine = operation.getNumMachine();

        // recuperation de l'operation precedente

        // on prend le maximum entre la distance entre les deux op et le temps de la machine
        // (pour le cas ou elle est deja utilisee)

        // si tout se passe bien --> chemin lineaire
        int job = itemVecBierwirth;
        int etape = jobEnCours - 1;

        // pepin --> zigzag
        if (jobEnCours > 0) {
            auto &opPrec = data.getMatreiceOp()[itemVecBierwirth][jobEnCours - 1];
            if (opPrec.getDuree() + dateDemarrage[itemVecBierwirth][jobEnCours - 1].demarragePlusTot <
                lastMachine[numMachine].dateLiberation) {
                job = lastMachine[numMachine].posMachine.first;
                etape = lastMachine[numMachine].posMachine.second;
            }
            // calcul du max
            max = std::max(opPrec.getDuree() +
                           dateDemarrage[itemVecBierwirth][jobEnCours - 1].demarragePlusTot,
                           lastMachine[numMachine].dateLiberation);
        } else {
            job = lastMachine[numMachine].posMachine.first;
            etape = lastMachine[numMachine].posMachine.second;
            max = lastMachine[numMachine].dateLiberation;
        }
        int lastMachi = lastMachine[numMachine].dateLiberation;

        // remplissage de la matrice
        dateDemarrage[itemVecBierwirth][jobEnCours] = chemin(max, job, etape);

        // mise a jour des donnees sur les machines
        lastMachine[numMachine].dateLiberation =
                operation.getDuree() + dateDemarrage[itemVecBierwirth][jobEnCours].demarragePlusTot;
        lastMachine[numMachine].posMachine = std::pair<int, int>(itemVecBierwirth, jobEnCours);
        makespan = std::max(makespan, max + operation.getDuree());
    }

    // mise a jour du makespan


    return 0;

}

void Bierwirth::affiche(std::ostream &flux) const {
    for (auto &i : vectBierwirth) {
        flux << i << " ";
    }
}

std::ostream &operator<<(std::ostream &flux, const Bierwirth &bierwirth) {
    bierwirth.affiche(flux);
    return flux;
}

matrice<Bierwirth::chemin> Bierwirth::getDateDemarrage() {
    return dateDemarrage;
}


int Bierwirth::recupMakespan() {
    return makespan;
}

int Bierwirth::getBestMakespan(Data &data, int GRASP) {
    evaluate(data);
    // do {
    // swap
    for (int j = 0; j < 10; j++) {

        for (int i = 0; i < vectBierwirth.size() - 1; ++i) {
            if (vectBierwirth[i] != vectBierwirth[i + 1]) {
                std::vector<int> copie = vectBierwirth;
                vectBierwirth = swapVecteur(i);
                matrice<chemin> copieDate = dateDemarrage;
                int makespancopie = makespan;
                raz();
                auto decalage = dateDemarrage.begin()+i+GRASP;
                if (decalage > dateDemarrage.end()) {
                    auto stop = decalage - dateDemarrage.end();
                    decalage = dateDemarrage.begin() + stop;
                }
                    std::random_shuffle(dateDemarrage.begin() + i, decalage);
                evaluate(data);
                if (makespan > makespancopie) {
                    vectBierwirth = copie;
                    makespan = makespancopie;
                    copieDate = dateDemarrage;

                }
            }


        }
        shuffle();
    }

    //} while (!stop);
    return makespan;
}

std::vector<int> Bierwirth::swapVecteur(int index) {
    std::vector<int> copie = vectBierwirth;
    // swap
    int toto = copie[index];
    copie[index] = copie[index + 1];
    copie[index + 1] = toto;
    return copie;
}


void Bierwirth::raz() {
    for (auto &i : lastJob) {
        i = -1;
    }
    for (auto &i :lastMachine) {
        i = dataLastMachine();
    }
    for (auto &i :dateDemarrage) {
        for (auto &path :i) {
            path = chemin();
        }
    }
    makespan = 0;
}












