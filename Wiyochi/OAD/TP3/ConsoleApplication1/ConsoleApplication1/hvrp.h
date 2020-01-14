#pragma once

#include "stdafx.h"
#include <string>
#include <fstream>
#include <cmath>
#include <set>
#include <iostream>
#include <iomanip>
#include <cstring>

const int nb_max_sommets_par_tournee = 50; // Nombre de sommets max par tourn�e (suppos�)
const int nb_max_tournees = 50; // Nombre de tourn�es max pour un probl�me (suppos�)
const int nb_max_types_vehicules = 10; // Nombre de type de v�hicules diff�rents (suppos�)
const int nb_max_sommets = 300; // Nombre de sommets max par instance (suppos�)
const int nb_max_labels = 200; // Nombre max de labels par sommets du graphe de split

struct t_tournee
{
	double cout; // Cout de la tourn�e
	int sommets[nb_max_sommets_par_tournee]{}; // Liste des sommets du trip avec (list[0] = list[-1]) 
	int nb_sommet; // Nombre de sommets parcourus
	int valeur; // Quantit� ramass�e
	int type; // Type du v�hicule utilis�
	double distance; // Distance parcourue pour faire la tournée
};

struct t_solution
{
	double cout_total; // Cout total de la solution
	t_tournee tournees[nb_max_tournees]{}; // Liste des tourn�es
	int nb_tournee; // Nombre de tourn�es effectu�es
};

struct t_vehicle
{
	int cout_f; // Cout fixe
	double cout_m; // Cout au km
	int quantite; // Quantit� total pouvant �tre transport�e par un v�hicule 
	int nb_vehicules; // Nombre de v�hicule de ce type
};

struct t_instance
{
	int nb_types_vehicules; // Nombre de type de v�hicules diff�rents
	t_vehicle vehicles[nb_max_types_vehicules]{}; // Liste des types de vehicules

	int nb_sommets; // Nombre de sommets de l'instance
	double distances[nb_max_sommets][nb_max_sommets]{}; // Matrice des distances entre les sommets
	int quantite[nb_max_sommets]{}; // Quantit� � r�cup�rer sur chaque sommet

	double limite; // Limite minimale th�orique du co�t
};

struct t_label
{
	double cout; // Cout cumule pour arriver à ce sommet
	int ressources[nb_max_types_vehicules]{}; // Ressources restantes à ce sommet
	int nb_ressources; // Taille du tableau
	t_label * prec; // Label précédent
	int noeud;
	int vehicule;
};

struct t_liste_label
{
	t_label liste[nb_max_labels]{}; // Ensemble des labels d'un sommet
	int nb_labels; // Nombre de labels sur ce sommet

	t_label& operator[](int i);
};

struct t_graphe_split
{
	t_liste_label liste[nb_max_sommets]{}; // Ensembles des sommets du graph
	int nb_sommets; // Nombre de sommet du graph

	t_liste_label& operator[](int i);
};

void charger_instance_coordonnees(t_instance& instance, const std::string& filename);
bool charger_instance_distances(t_instance& instance, const std::string& filename);
void generer_tour_geant_alea(int taille_tour, int * T);
void generer_tour_geant_ppv(t_instance& instance, int * T);
void generer_tour_geant_ppvr(t_instance& instance, int * T);
void generer_tour_geant(t_instance& instance, int * T);
bool opt(t_instance& instance, t_solution & sol);
bool opt_insertion(t_instance& instance, t_solution& sol);
bool opt_inter_tournees(t_instance& instance, t_solution& sol);
void ajouter_label(t_liste_label& liste, t_label& label);
void split(t_instance& instance, int * T, t_graphe_split& graph);
void decalage_droite(int v[5], int k);
void teste_de_dominance();
int domine(t_label const & P1, t_label const & P2);
void afficher_solution(t_solution& sol);
void afficher_label(t_label const & lab);
bool from_split_to_tournee(t_instance& instance, int * T, t_graphe_split& graph, t_solution& solution);
double calcul_cout(t_instance& instance, t_tournee& tournee);
void grasp(t_instance& instance, t_solution& sol);