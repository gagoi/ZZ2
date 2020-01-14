/**
 * @file FemaleRabbit.hpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier de déclaration de la classe FemaleRabbit
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef FEMALERABBIT_H_
#define FEMALERABBIT_H_

#include "global.hpp"
#include "Rabbit.hpp"

/**
 * @class FemaleRabbit
 * @brief Classe représentant un lapin femelle
 * 
 */
class FemaleRabbit : public Rabbit
{
public:
    FemaleRabbit(std::list<Rabbit*> & pop);
    ~FemaleRabbit();

    virtual void grow();
    virtual bool isMale() const;

private:
    bool                    _monthsToBirth[12]; //!< représente les mois où la femelle doit enfanter, si monthToBirth[i] vrai -> la lapine doit enfanter au mois i
    std::list<Rabbit*> &    _whereToGiveChildren; //!< représente la population où la femelle doit y "ajouter" ses enfants
};

#endif