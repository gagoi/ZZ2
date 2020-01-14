//
// Created by unnom on 25/10/16.
//

#include "compare.hpp"
#include <string>
#include "Bierwirth.hpp"
#include "Data.h"
#include "bkr.hpp"

void compareSolution(int GRASP) {

    for ( int i = 1 ; i <= 40 ; i++){
        std::string path = "../../INSTANCES/la";
        if (i < 10){
            path+= "0"+std::to_string(i);
        }else{
            path+=std::to_string(i);
        }
        path+=".dat";

        Data data(path);
        Bierwirth bierwirth(data.getNbEtape(), data.getNbOp());
        BKR bkr(data);
        //std::cout << "\033[0mPour le fichier\033[32m " << path << "\033[0m la meilleure solution est :\033[31m" << bkr << "\033[0m notre solution : \033[34m" << bierwirth.getBestMakespan(data, GRASP) << std::endl;
    }
}
