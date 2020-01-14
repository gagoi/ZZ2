// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

const int max_sommet = 300;
const int max_successeur = 20;
const int inf = 999;

typedef struct graphe {
	int n;
	int NS[max_sommet];
	int S[max_sommet][max_successeur];
	float P[max_sommet][max_successeur];
} graphe_t;

typedef struct chemin {
	int sommet_depart;
	int sommet_final;
	int m[max_sommet];
	int pred[max_sommet];
} chemin_t;

void calculer_chemin_bellman(int depart, int fin, graphe_t& graphe, chemin_t& chemin)
{
	int T[max_sommet];
	int ordre[max_sommet];
	bool stop = false;
	int cpt = 0;
	chemin.sommet_depart = depart;
	chemin.sommet_final = fin;

	for (size_t i = 1; i <= graphe.n; i++)
	{
		chemin.m[i] = inf;
		T[i] = 0;
		ordre[i] = graphe.n - i + 1;
	}
	chemin.m[chemin.sommet_depart] = 0;

	for (size_t k = 0; k < graphe.n; k++)
	{
		for (size_t i = 1; i <= graphe.n; i++)
		{
			int choisit = ordre[i];
			for (size_t j = 0; j < graphe.NS[choisit]; j++)
			{
				int k = graphe.S[choisit][j];
				if (chemin.m[choisit] + graphe.P[choisit][j] < chemin.m[k])
				{
					chemin.m[k] = chemin.m[choisit] + graphe.P[choisit][j];
					chemin.pred[k] = choisit;
				}
			}
		}
	}
}

void calculer_chemin_dijkstra(int depart, int fin, graphe_t& graphe, chemin_t& chemin)
{
	int T[max_sommet];
	chemin.sommet_depart = depart;
	chemin.sommet_final = fin;

	for (size_t i = 1; i <= graphe.n; i++)
	{
		chemin.m[i] = inf;
		T[i] = 0;
	}
	chemin.m[chemin.sommet_depart] = 0;

	for (size_t i = 1; i <= graphe.n; i++)
	{
		int min = inf;
		int nmin = 0;
		for (size_t j = 1; j <= graphe.n; j++)
		{
			if (chemin.m[j] < min && T[j] == 0)
			{
				min = chemin.m[j];
				nmin = j;
			}
		}

		for (size_t j = 0; j < graphe.NS[nmin]; j++)
		{
			int k = graphe.S[nmin][j];
			if (chemin.m[nmin] + graphe.P[nmin][j] < chemin.m[k])
			{
				chemin.m[k] = chemin.m[nmin] + graphe.P[nmin][j];
				chemin.pred[k] = nmin;
			}
		}
		T[nmin] = 1;
	}

}

void lire_graphe(std::string nom_fichier, graphe_t& graphe)
{
	std::ifstream f(nom_fichier);

	if (f)
	{
		f >> graphe.n;

		for (size_t i = 1; i <= graphe.n; i++)
		{
			f >> graphe.NS[i];
			for (size_t j = 0; j < graphe.NS[i]; j++)
			{
				f >> graphe.S[i][j];
				f >> graphe.P[i][j];
			}
		}
		f.close();
	}
}

void afficher_chemin(chemin& c)
{
	int sommet = c.sommet_final;

	while (c.m[sommet] != 0)
	{
		std::cout << sommet << std::endl;
		sommet = c.pred[sommet];
	}
	std::cout << sommet << std::endl;
}


int main()
{
	graphe_t g;
	chemin_t c_dijkstra;
	chemin_t c_bellman;
	std::chrono::time_point<std::chrono::steady_clock> t1, t2;

	lire_graphe("graph.txt", g);


	t1 = std::chrono::high_resolution_clock::now();
	calculer_chemin_dijkstra(1, 210, g, c_dijkstra);
	t2 = std::chrono::high_resolution_clock::now();

	std::cout << "DIJKSTRA: "<< std::chrono::duration<double>(t2 - t1).count() * 1000 << std::endl;
	afficher_chemin(c_dijkstra);


	t1 = std::chrono::high_resolution_clock::now();
	calculer_chemin_bellman(1, 210, g, c_bellman);
	t2 = std::chrono::high_resolution_clock::now();

	std::cout << "BELLMAN: " << std::chrono::duration<double>(t2 - t1).count() * 1000 << std::endl;
	afficher_chemin(c_bellman);

	system("PAUSE");

	return 0;
}

