/**
 * @file Rabbit.hpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier de déclaration de la classe Rabbit
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef RABBIT_H_
#define RABBIT_H_

#include "global.hpp"

/**
 * @class Rabbit
 * @brief Classe représentant un lapin (mâle ou femelle)
 * 
 * Si l'objet est créé en tant que Rabbit, c'est qu'il représente un lapin mâle, sinon la classe utilisée sera FemaleRabbit.
 * Cependant la classe Rabbit synthétise les deux genres. Il n'y a juste pas de classe MaleRabbit puisque celle-ci n'implémenterait rien de plus que la classe Rabbit.
 */
class Rabbit
{
public:
    Rabbit();
    virtual ~Rabbit();
    
    virtual void    grow();
    bool            hasMajority() const;
    bool            hasToDie() const;
    unsigned int    getAge() const;
    virtual bool    isMale() const;

    static constexpr double survival_proba_young = 0.2; //!< probabilité de survivre à la jeunesse (les 5 à 8 premiers mois)
    static constexpr double survival_proba_adult = 0.5; //!< probabilité de survivre pour un lapin adulte (11 ans moins les mois de jeunesse)

protected:
    unsigned int    _age; //!< L'age du lapin en mois
    unsigned int    _majority; //!< Nombre de mois avant que le lapin n'atteigne la majorité et passe à l'age adulte et puisse enfanter (si c'est une femelle)
    double          _proba_to_die_young; //!< Probabilité de mourir (par mois) avant de devenir adulte, calculée avec la probabilité de survivre et le nombre de mois de jeunesse
    double          _proba_to_die_adult; //!< Probabilité de mourir (par mois) en étant adulte, calculée avec la probabilité de survivre et le nombre de mois de jeunesse
};


#endif