/**
 * @file Population.cpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier d'implémentation de la classe Population
 * @version 0.1
 * @date 2019-11-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Population.hpp"

/**
 * @brief Construit un nouvel objet "Population"
 * 
 * Initialise la population avec 1 lapin mâle et 1 lapin femelle 
 */
Population::Population() :
    _month(0),
    _nbDeath(0),
    _nbBirth(2),
    _sumDeathAge(0)
{
    _population.push_back(new Rabbit());
    _population.push_back(new FemaleRabbit(_population));
}

/**
 * @brief Construit un nouvel objet "Population"
 * 
 * Initialise la population avec un nombre spécifié de mâles et de femelles
 * 
 * @param[in] numberOfMale nombre de mâles à la date 0 dans la population
 * @param[in] numberOfFemale nombre de femelles à la date 0 dans la population
 */
Population::Population(unsigned int numberOfMale, unsigned int numberOfFemale) :
    _month(0),
    _nbDeath(0),
    _nbBirth(0),
    _sumDeathAge(0)
{
    for (size_t i = 0; i < numberOfMale; i++)
        _population.push_back(new Rabbit());
    for (size_t i = 0; i < numberOfFemale; i++)
        _population.push_back(new FemaleRabbit(_population));
    _nbBirth = _population.size();  
}

/**
 * @brief Détruit l'objet "Population"
 * 
 * Désalloue la mémoire allouée par les lapins de la population
 */
Population::~Population()
{
    std::for_each(_population.begin(), _population.end(), [](Rabbit*& r){ delete r; });
}

/**
 * @brief passe le temps pour la population de lapins
 * 
 * Passe un nombre de mois spécifié pour tous les lapins de la population
 * La méthode les fait grandir avec la fonction grow, et si des lapins meurent, les supprime de la liste
 * 
 * @param[in] nbOfMonths nombre de mois que l'on veut passer
 */
void Population::passTime(unsigned int nbOfMonths)
{
    for (size_t i = 0; i < nbOfMonths; i++)
    {
        size_t sizeBeforeGrowth = _population.size();

        // On fait grandir tous les lapins de 1 mois
        std::for_each(_population.begin(), _population.end(),[](Rabbit* const & r)
        {
            r->grow();
        });

        // On compte le nombre de naissances de mois
        _nbBirth += _population.size() - sizeBeforeGrowth;

        // On regarde si des lapins meurent ce mois
        std::for_each(_population.begin(), _population.end(),[this](Rabbit*& r)
        {
            if (r->hasToDie())
            {
                _sumDeathAge += r->getAge();
                delete r;
                r = nullptr;
                // On compte le nombre de morts ce mois
                _nbDeath++;
            }
        });
        // On retire les lapins morts de la population
        _population.remove(nullptr);
    }
    _month += nbOfMonths;
}

/**
 * @brief getter pour le nombre de mois passés par la population
 * 
 * @return unsigned int nombre de mois passés par la population
 */
unsigned int Population::getMonth() const
{
    return _month;
}

/**
 * @brief getter pour le nombre de lapins de la population à l'instant t
 * 
 * @return size_t nombre de lapins (vivants) dans la population
 */
size_t Population::getNumberOfRabbit() const
{
    return _population.size();
}

/**
 * @brief getter pour le nombre de femelles dans la poplation à l'instant t
 * 
 * @return size_t nombre de lapins femelles dans la population
 */
size_t Population::getNumberOfFemaleRabbit() const
{
    size_t n = 0;
    std::for_each(_population.begin(), _population.end(), [&](Rabbit* r)
    {
        if (!r->isMale())
            n++;
    });
    return n;
}

/**
 * @brief getter pour le nombre de mâles dans la poplation à l'instant t
 * 
 * @return size_t nombre de lapins mâles dans la population
 */
size_t Population::getNumberOfMaleRabbit() const
{
    size_t n = 0;
    std::for_each(_population.begin(), _population.end(), [&](Rabbit* r)
    {
        if (r->isMale())
            n++;
    });
    return n;
}

/**
 * @brief getter pour le nombre de morts depuis le début de la population
 * 
 * @return size_t nombre de morts
 */
size_t Population::getDeath() const
{
    return _nbDeath;
}

/**
 * @brief getter pour le nombre de naissances depuis le début de la population
 * 
 * @return size_t nombre de naissances
 */
size_t Population::getBirth() const
{
    return _nbBirth;
}

/**
 * @brief getter pour la moyenne d'age auquel les lapins meurent
 * 
 * @return double moyenne d'age de mort
 */
double Population::getMeanDeathAge() const
{
    return static_cast<double>(_sumDeathAge) / _nbDeath;
}

/**
 * @brief ecrit dans un fichier les statistiques de la population à l'instant t
 * 
 * @param[in] filename nom du fichier dans lequel on ajoute une ligne de statistiques
 */
void Population::exportToCSV(std::string const & filename)
{
    std::ofstream file(filename, std::ios::app);

    if (file)
    {
        file << _month << "\t" << getNumberOfRabbit() << std::endl;
    }
}

/**
 * @brief surcharge de l'opérateur <<
 * 
 * Ecrit dans un flux donné l'état actuel de la population
 * 
 * @param[in] out flux de sortie dans lequel on écrit
 * @param[in] pop population dont on veut écrire l'état
 * @return std::ostream& flux de sortie
 */
std::ostream& operator<<(std::ostream& out, Population const & pop)
{
    out << "Population: " << std::endl;
    out << "  Male:  \t" << pop.getNumberOfMaleRabbit() << std::endl;
    out << "  Female:\t" << pop.getNumberOfFemaleRabbit() << std::endl;
    out << "  Total: \t" << pop.getNumberOfRabbit() << std::endl << std::endl;
    out << "  Birth: \t" << pop.getBirth() << std::endl;
    out << "  Death: \t" << pop.getDeath() << std::endl;
    out << "  Mean of death age: \t" << pop.getMeanDeathAge() << std::endl;
    return out;
}