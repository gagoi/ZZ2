#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>

constexpr int max_piece = 30;
constexpr int max_machine = 15;

constexpr unsigned int max_hashs = 9999;

struct t_instance
{
	int nb_pieces{};
	int nb_machines{};
	int sequences[max_piece][max_machine]{};
	int durees[max_piece][max_machine]{};
	unsigned long hashs[max_hashs]{};
};

struct t_solution
{
	int taille{};							// Taille des différents tableaux (max_piece * max_machine)
	int vb[max_piece * max_machine]{}; 	// Vecteur de Bierwirth
	int st[max_piece * max_machine]{};	// Starting times
	int Pp[max_piece * max_machine]{}; 	// Durees (linearisees)
	int Pred[max_piece * max_machine]{};	// Predecesseurs
	int N[max_piece]{}; 				// Nombre d'occ de chaque machine
	int T[max_piece][max_machine]{}; 		// Ordre
	int t[max_piece * max_machine]{};		// Obtenir le numéro de pièce à partir d'un index
	int t2[max_piece * max_machine]{};	// Obtenir l'occurence à partir d'un index
	int MP[max_machine]{}; 				// Derniere piece passe sur chaque machine
	int Mm[max_piece * max_machine]{}; 	// Sequences (linearise)
	int temps_total{}; 					// Temps qu'il faut pour arriver à terme de la totalité des étapes
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