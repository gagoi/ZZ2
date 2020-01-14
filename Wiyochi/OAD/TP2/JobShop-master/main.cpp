#include <iostream>
#include "Operation.hpp"
#include "Data.h"
#include "Bierwirth.hpp"
#include "bkr.hpp"
#include "compare.hpp"
/*
int main(int , char ** argv) {
    Data data("INSTANCES/la01.dat");
    std::cout << data;
    Bierwirth bierwirth(data.getNbEtape(), data.getNbOp());
    std::cout << bierwirth << std::endl;


    compareSolution();
    std::cout <<std::endl;
    compareSolution(10);
    return 0;
}*/
/**
 * Pour chaque operation dans la matrice on a la position dans le vecteur de bierwirth
 *
 * Le chemin critique:
 *                    recommence:
     *                    arc disjonctif, le job suivant n'est pas le meme que le job en cours
     *                    on va travailler sur les arcs disjonctifs
     *                    on swap les arcs disjonctif, dans le vecteur de Bierwirth 1 2 -> 2 1
         *                    on copie le vecteur de B
         *                    et on swap un arc
         *                    on evalue -> on obtiens au autre makespan = matrice obtenue par l'evaluation, on va prendre la derniere val
     *                    si val makespan copie < makespan
     *                        cool on a un truc meilleur
 *                    goto recommence
 *
 *                    Algo :
 *                    Vecbierwrth b0
 *                    Faire
 *                          evaluer b0
 *                          calculer chemin critique b0
 *                          best = +oo
 *                          pour tout disjonction  (a,b) appartient chemin critique
 *                              b0 -> b'
 *                              swap(a,b)
 *                              evaluer(b')
 *                              si makespan(b') < makespan(best)
 *                                      best <- b'
 *                          si makespan(best) < makespan(b0)
 *                                  b0 <- best
 *                          sinon
 *                              stop = vrai
 *                      tant que (!stop)
 *
 *                      MultiStart
 *                          best = +oo
 *                          Pour i : 0, max
 *                                  b0 = Bierwirth aleat
 *                                  RL(b0) -> b'
 *                                  si makespan(b') < makspan(best)
 *                                      best <- b'
 *                          return makespan(best)
 *
*/
