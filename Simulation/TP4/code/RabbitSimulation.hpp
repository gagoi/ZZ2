/**
 * @file RabbitSimulation.hpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @brief Classe déclarant le comportement d'une simulation de population de lapin.
 * @version 0.1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RABBITSIMULATION_HPP_
#define RABBITSIMULATION_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <list>

#include "Rabbit.hpp"
#include "RabbitFemale.hpp"

class RabbitSimulation
{
private:
	// Générateur de Mersenne-Twister de cette simulation.
	std::mt19937 _generator;

	// Identifiant de la prochaine simulation créée
	static ushort run_id;
	// Version string de cette identifiant, pour les fichiers.
	static std::string run_id_str;

	// Identifiant unique de cette simulation
	ushort _run_id;

	// Liste des lapins
	std::list<Rabbit*> _males;
	std::list<RabbitFemale*> _females;

	// Faire l'étape de naissances
	void births();
	// Faire vieillir les lapins
	void grow();
	// Faire l'étape de mort
	void die();

	// Age de la simulation en semaine
	unsigned int _week;

	unsigned int _nb_males_init;
	unsigned int _nb_females_init;

	/////////////////////////////////////////////////////////
	///////////////////// Measurement ///////////////////////
	/////////////////////////////////////////////////////////
	// Nombre de lapins intégrés à la simulation
	unsigned int _nb_rabbits_total;
	// Nombre de mâles intégrés à la simulation
	unsigned int _nb_males_total;
	// Nombre de femelles intégrées à la simulation
	unsigned int _nb_females_total;

	// Nombre de lapereaux mâles morts
	unsigned int _nb_childs_males_deaths;
	// Nombre de lapereaux femelles mortes
	unsigned int _nb_childs_females_deaths;
	// Nombre de lapins morts
	unsigned int _nb_adults_males_deaths;
	// Nombre de lapines mortes
	unsigned int _nb_adults_females_deaths;

	// Permet de connaître le nombre d'enfants mâles en vie
	unsigned int get_childs_nb(std::list<Rabbit*> _list);
	// Permet de connaître le nombre d'enfants femelles en vie
	unsigned int get_childs_nb(std::list<RabbitFemale*> _list);

	// Fichier qui contiendra l'évolution du nombre de lapins
	std::ofstream _file1;
	// Fichier qui contiendra l'évolution du nombre de lapins femelles
	std::ofstream _file2;
	// Fichier qui contiendra l'évolution du nombre de lapins mâles
	std::ofstream _file3;
	// Fichier qui contiendra le nombre de portées de chaque lapine
	std::ofstream _file4;
	// Fichier qui contiendra le nombre de bébés par portée
	std::ofstream _file5;
	// Fichier qui contiendra le sexe des bébés
	std::ofstream _file6;
	// Fichier qui contiendra la date de mort des lapins
	std::ofstream _file7;
	// Fichier qui contiendra le ratio de période de la mort des lapins
	std::ofstream _file8;
	// Fichier qui contiendra l'age de maturité des lapins
	std::ofstream _file9;
	// Fichier qui contiendra le nombre de portées normalisé
	std::ofstream _file10;

	// Prépare les fichiers
	void init_datas();
	// Ajouteles informations au fichier
	void log_datas();


    std::map<int, int> _gender_histo{};
    std::map<int, int> _baby_histo{};
    std::map<int, int> _delay_histo{};
	std::map<int, int> _death_histo{};
    std::map<int, int> _death_period_histo{};
	std::map<int, int> _maturity_histo{};
	
public:
	// Créer une nouvelle simulation de population de lapins
	RabbitSimulation(unsigned int rand_init, unsigned int nb_males_init = 2, unsigned int nb_females_init = 2);
	// Libère la mémoire allouée à une simulation
	~RabbitSimulation();

	// Lance la simulation pour une durée donnée
	void run(unsigned int week);
};
#endif
