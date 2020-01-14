#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>

constexpr int max_piece = 30;					// Nombre de pièce maximum pour chaque instance
constexpr int max_machine = 15;					// Nombre de machine maximum pour chaque instance

constexpr unsigned int max_hashs = 9999; 		// Taille de la table de hachage

struct t_instance
{
	int nb_pieces{}; 							// Nombre de pièce de l'instance
	int nb_machines{};							// Nombre de machine de l'instance
	int sequences[max_piece][max_machine]{};	// Séquence des taches 
	int durees[max_piece][max_machine]{};		// Durée de chaque de tache
	unsigned long hashs[max_hashs]{};			// Table de hachage
};

struct t_solution
{
	int taille{};								// Taille des différents tableaux (max_piece * max_machine)
	int vb[max_piece * max_machine]{}; 			// Vecteur de Bierwirth
	int st[max_piece * max_machine]{};			// Starting times
	int Pp[max_piece * max_machine]{}; 			// Durees (linearisees)
	int Pred[max_piece * max_machine]{};		// Predecesseurs
	int N[max_piece]{}; 						// Nombre de fois où l'on travaille sur une pièce
	int T[max_piece][max_machine]{}; 			// Ordre de traitement des taches
	int t[max_piece * max_machine]{};			// Obtenir le numéro de pièce à partir d'un index
	int t2[max_piece * max_machine]{};			// Obtenir l'occurence à partir d'un index
	int MP[max_machine]{}; 						// Derniere piece passe sur chaque machine
	int Mm[max_piece * max_machine]{}; 			// Sequences (linearise)
	int temps_total{}; 							// Temps qu'il faut pour arriver à terme de la totalité des étapes
};


void lire_fichier(std::string nom_fichier, t_instance& instance);
void generer_vb(t_solution& solution,const t_instance& instance);
void init_evaluer(t_solution& solution,const t_instance& instance);
void evaluer(t_solution& solution);
void recherche_locale(t_solution& solution, const t_instance& instance);
void afficher_solution(const t_solution& solution, const t_instance& instance);
bool verifier_solution(const t_solution& solution);
long calculer_hash(const t_solution& t_solution);
void grasp(t_solution& solution, t_instance& instance);