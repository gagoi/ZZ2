/**
 * @file Population.hpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier de déclaration de la classe Population
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef POPULATION_H_
#define POPULATION_H_

#include <fstream>
#include "global.hpp"
#include "FemaleRabbit.hpp"
#include "Rabbit.hpp"

/**
 * @class Population
 * @brief Représente une population de lapins
 * 
 */
class Population
{
public:
    Population();
    Population(unsigned int numberOfMale, unsigned int numberOfFemale);
    ~Population();

    void passTime(unsigned int nbOfMonths);
    unsigned int getMonth() const;
    size_t getNumberOfRabbit() const;
    size_t getNumberOfFemaleRabbit() const;
    size_t getNumberOfMaleRabbit() const;
    size_t getDeath() const;
    size_t getBirth() const;
    double getMeanDeathAge() const;

    void exportToCSV(std::string const & filename);

private:
    std::list<Rabbit*> _population; //!< liste de lapins constituants la population
    unsigned int _month; //!< nombre de mois passé par la population
    unsigned int _nbDeath; //!< nombre de morts dans la population (depuis le début)
    unsigned int _nbBirth; //!< nombre de naissances dans la population (depuis le début)
    unsigned int _sumDeathAge; //!< somme des ages auquels meurent les lapins
};

std::ostream& operator<<(std::ostream& out, Population const & pop);

#endif