/**
 * @file FemaleRabbit.cpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier d'implémentation de la classe FemaleRabbit
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "FemaleRabbit.hpp"

/**
 * @brief Construit un nouvel objet "Female Rabbit"
 * 
 * Le constructeur de FemaleRabbit appelle le constructeur de Rabbit afin d'initialiser les variables (telles que l'âge et les probabilités de mourir)
 * 
 * @param[in] pop liste représentant la population de lapins où la femelle créée devra enfanter
 */
FemaleRabbit::FemaleRabbit(std::list<Rabbit*> & pop) :
    Rabbit(),
    _whereToGiveChildren(pop)
{
    std::memset(_monthsToBirth, false, 12);
}

/**
 * @brief Détruit l'objet "Female Rabbit"
 * 
 */
FemaleRabbit::~FemaleRabbit()
{
}

/**
 * @brief Méthode faisant vieillir le lapin de 1 mois
 * 
 * Appelle la méthode grow de Rabbit afin de grandir en tant que lapin
 * Si c'est l'anniversaire de la lapine, les mois auquels elle enfante dans l'année sont choisis
 * Si c'est un mois où elle doit enfanter, le nombre de bébés lapins dans la portée est décidé et elle rajoute ce nombre de nouveaux lapins à la population
 */
void FemaleRabbit::grow()
{
    Rabbit::grow();

    // Happy birthday!
    if(_age % 12 == 0)
    {
        // On décide combien de portées la lapine aura cette année
        int nbOfLitters = dis_normal_6_1(generator);

        std::memset(_monthsToBirth, false, 12);

        // On regarde si il y a au moins 1 male dans la population qui a la majorité et si la lapine a la majorité
        if (std::any_of(_whereToGiveChildren.begin(), _whereToGiveChildren.end(), [](Rabbit* r) { return r->isMale() && r->hasMajority(); }) && hasMajority())
        {
            // On décide à l'avance les mois auquel la lapine enfante
            for (int i = 0; i < nbOfLitters; i++)
            {
                int month = dis_int_0_11(generator);
                _monthsToBirth[month] = true;
            }
        }
    }

    // Si ce mois la lapine doit enfanter
    if(_monthsToBirth[_age % 12])
    {
        // On décide le nombre de bébés de la portée
        int nbOfChildren = dis_int_3_6(generator);
        for (int i = 0; i < nbOfChildren; i++)
        {
            // Nouvelle naissance -> 50% de chance d'avoir un male / 50% de chance d'avoir une femelle
            double random = dis_real_0_1(generator);
            _whereToGiveChildren.push_back(random < 0.5 ? new Rabbit() : new FemaleRabbit(_whereToGiveChildren));
        }
        
    }
}

/**
 * @brief Méthode permettant de savoir si l'instance est celle d'un lapin mâle ou femelle 
 */
bool FemaleRabbit::isMale() const
{
    return false;
}