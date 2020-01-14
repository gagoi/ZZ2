/**
 * @file Rabbit.cpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier d'implémentation de la classe Rabbit
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Rabbit.hpp"

/**
 * @brief Construit un nouvel objet "Rabbit"
 * 
 * Définit l'age de la majorité, la probabilité de mourir jeune et la probabilité de mourir en étant adulte 
 */
Rabbit::Rabbit() :
    _age(0),
    _majority(dis_int_5_8(generator)),
    _proba_to_die_young(std::pow(survival_proba_young, 1.0 / _majority)),
    _proba_to_die_adult(std::pow(survival_proba_adult, 1.0 / (132 - _majority)))
{
}

/**
 * @brief Détruit l'objet "Rabbit"
 */
Rabbit::~Rabbit()
{
}

/**
 * @brief Méthode qui fait veillir l'instance d'un lapin de 1 mois
 */
void Rabbit::grow()
{
    _age += 1; // + 1 mois
}

/**
 * @brief Méthode pour savoir si le lapin est jeune ou adulte
 * 
 * @return true si le lapin est adulte
 * @return false si le lapin est jeune
 */
bool Rabbit::hasMajority() const
{
    return _age >= _majority;
}

/**
 * @brief Méthode pour savoir si le lapin doit mourir ce mois
 * 
 * @return true si il doit mourir
 * @return false si il survit
 */
bool Rabbit::hasToDie() const
{
    return hasMajority() ? _proba_to_die_adult < dis_real_0_1(generator) : _proba_to_die_young < dis_real_0_1(generator);
}

/**
 * @brief Getter pour l'age
 * 
 * @return unsigned int l'age du lapin
 */
unsigned int Rabbit::getAge() const
{
    return _age;
}

/**
 * @brief Méthode permettant de savoir si l'instance est celle d'un lapin mâle ou femelle
 */
bool Rabbit::isMale() const
{
    return true;
}