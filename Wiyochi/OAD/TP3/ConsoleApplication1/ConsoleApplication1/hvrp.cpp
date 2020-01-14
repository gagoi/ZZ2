#include "hvrp.h"

/*
	Fonction qui permet charger une instance d'un probleme à partir d'un fichier sous un certain format
	entrees : filename, nom du fichier à charger
	sorties : instance, structure contenant les informations d'un problème (distance entre les points, véhicules)
*/
void charger_instance_coordonnees(t_instance& instance, const std::string& filename)
{
	std::ifstream fichier(filename);
	std::string ligne;
	double poubelle;
	int x[nb_max_sommets];
	int y[nb_max_sommets];
	
	if (fichier)
	{
		// getlines qui permettent de passer les lignes commentaires des fichiers
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);

		fichier >> instance.nb_sommets;
		fichier >> instance.nb_types_vehicules;

		// Permet de passer des éléments du fichier qu'on ne garde pas dans l'instance
		fichier >> poubelle;
		fichier >> poubelle;

		fichier >> instance.limite;

		fichier >> poubelle;

		// On récupère les informations de tous les véhicules
		for (size_t i = 0; i < instance.nb_types_vehicules; i++)
		{
			fichier >> instance.vehicles[i].nb_vehicules;
			fichier >> instance.vehicles[i].quantite;
			fichier >> instance.vehicles[i].cout_f;
			fichier >> instance.vehicles[i].cout_m;
		}

		// Le premier sommet est le départ de toutes les tournées
		// On conserve uniquement les positions dans des tableaux temporaires
		fichier >> x[0];
		fichier >> y[0];
		instance.quantite[0] = 0;

		// On récupère toutes les positions des sommets
		for (size_t i = 1; i < instance.nb_sommets; i++)
		{
			fichier >> x[i];
			fichier >> y[i];
			fichier >> instance.quantite[i];
		}

		// On calcule toutes les distances
		for (size_t i = 0; i < instance.nb_sommets; i++)
		{
			for (size_t j = 0; j < instance.nb_sommets; j++)
			{
				instance.distances[i][j] = 1000*std::sqrt(std::abs(x[i] * x[i] - y[j] * y[j]));
			}
		}

		fichier.close();
	}


}

/*
	Fonction qui permet charger une instance d'un probleme à partir d'un fichier sous un certain format
	entrees : filename, nom du fichier à charger
	sorties : instance, structure contenant les informations d'un problème (distance entre les points, véhicules)
*/
bool charger_instance_distances(t_instance& instance, const std::string& filename)
{	
	std::ifstream fichier(filename);
	std::string ligne;
	double poubelle;

	if (fichier)
	{
		// getlines qui permettent de passer les lignes commentaires des fichiers
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);

		fichier >> instance.nb_sommets;
		fichier >> instance.nb_types_vehicules;

		// Permet de passer des éléments du fichier qu'on ne garde pas dans l'instance
		fichier >> poubelle;
		fichier >> poubelle;
		fichier >> poubelle;
		fichier >> poubelle;

		// On récupère les informations de tous les véhicules
		for (size_t i = 0; i < instance.nb_types_vehicules; i++)
		{
			fichier >> instance.vehicles[i].nb_vehicules;
			fichier >> instance.vehicles[i].quantite;
			fichier >> instance.vehicles[i].cout_f;
			fichier >> instance.vehicles[i].cout_m;
		}

		getline(fichier, ligne);
		getline(fichier, ligne);

		// On récupère la matrices des distances
		for (int i = 0; i < instance.nb_sommets + 1; ++i)
			for (int j = 0; j < instance.nb_sommets + 1; ++j)
				fichier >> instance.distances[i][j];

		getline(fichier, ligne);
		getline(fichier, ligne);

		// On récupère les quantités de chaque sommet
		for (int i = 0; i < instance.nb_sommets; ++i)
		{
			fichier >> poubelle;
			fichier >> instance.quantite[i];
		}

		fichier.close();
		return true;
	}
	else
	{
		return false;
	}
	
	
}

/*
	Fonction qui permet de generer un tour geant de manière totalment aléatoire
	entrees : taille_tour, taille de la tournee à générer
	sorties : tournee, tableau d'entier représentant les sommets
*/
void generer_tour_geant_alea(int taille_tour, int * tournee)
{
	// On se sert d'un tableau dont on réduit la taille et on inverse le dernier element avec l'element qu'on a choisi aléatoirement
	int max = taille_tour;
	int tab_alea[nb_max_sommets];
	for (int i = 0; i < taille_tour; i++)
		tab_alea[i] = i;

	for (int i = 0; i < taille_tour; i++)
	{
		int ind = rand() % max;
		tournee[i] = tab_alea[ind];

		tab_alea[ind] = tab_alea[max - 1];
		max--;
	}
}

/*
	Fonction qui permet de décaler les éléments d'un tableau (elle est utile pour la génération d'un tour géant avec la méthode des plus proches voisins randomisés)
	entrees : v, tableau des 5 plus proches voisins
			  k, limite pour faire le décalage
*/
void decalage_droite(int v[5], int k)
{
	for (int i = 4; i >= k; --i)
		v[i] = v[i - 1];
}

/*
	Fonction qui permet de generer un tour geant basique (avec l'ordre des sommets). Cette fonction a servie pour le débuggage des fonctions comme split ou les opérateurs alors
		que la génération des plus proches voisins et plus proche voisins randomisés n'étaient pas encore au point
	entrees : instance, instance dont on veut générer une solution
	sorties : T, tour géant
*/
void generer_tour_geant(t_instance& instance, int * T)
{
	for (int i = 0; i < instance.nb_sommets; ++i)
		T[i] = i + 1;
}

/*
	Fonction qui génère un tour géant avec la méthode des plus proches voisins
	entrees : instance, instance dont on veut générer une solution
	sorties : T, tour géant
*/
void generer_tour_geant_ppv(t_instance& instance, int * T)
{
	T[0] = 1; // On initialise l'algo pour démarrer au premier sommet
	int L[nb_max_sommets + 1]; // Liste contenant les sommets
	for (int i = 0; i < instance.nb_sommets + 1; i++)
		L[i] = i + 1; // Chaque sommet est représenté par un nombre
	bool M[nb_max_sommets + 1]{0};
	int pv0 = 0;
	int x, y;
	int Px = 0; // Index du premier sommet dans la liste L
	int nr = instance.nb_sommets - 1; // Nombre de sommets pas encore traites
	

	for (int i = 1; i < instance.nb_sommets; i++)
	{
		x = T[i - 1]; // Sommet de départ 
		// Suppression du sommet dans la liste
		L[Px] = L[nr]; // On retire l'ancien sommet de la liste.

		int pv0 = 0;
		int v0 = L[0];
		for (int j = 1; j < nr; j++) // Pour chaque sommet restant (rappel : on a retiré x)
		{
			y = L[j]; // Sommet actuel
			if (!M[y] && instance.distances[x][y] < instance.distances[x][v0]) // Si la distance est plus courte, on insere le sommet
			{
				v0 = y; // insertion de l'élément choisi
				pv0 = j;
			}
			
		}

		// Boucle de choix du voisin
		T[i] = v0;
		Px = pv0;
		M[v0] = true;
			
		nr--;
	}
}

/*
	Fonction qui génère un tour géant avec la méthode des plus proches voisins randomisés. On choisit les 5 plus proches voisins, puis on ajoute
		dans le tour géant un de ces voisin aléatoirement, avec une probabilité de 80% pour le premier, 80% des 20% restants pour le deuxième etc
	entrees : instance, instance dont on veut générer une solution
	sorties : T, tour géant
*/
void generer_tour_geant_ppvr(t_instance& instance, int * T)
{
	T[0] = 1; // On initialise l'algo pour démarrer au premier sommet
	int L[nb_max_sommets + 1]{}; // Liste contenant les sommets
	for (int i = 0; i < instance.nb_sommets + 1; i++)
		L[i] = i + 1; // Chaque sommet est représenté par un nombre
	int V[5]; // Liste des 5 plus proches voisins
	int pV[5]; // Position dans L des 5 plus proches voisins

	int x, y;
	int Px = 0; // Index du premier sommet dans la liste L
	int nr = instance.nb_sommets - 1; // Nombre de sommets pas encore traites
	

	for (int i = 1; i < instance.nb_sommets; i++)
	{
		x = T[i - 1]; // Sommet de départ 
		// Suppression du sommet dans la liste
		L[Px] = L[nr]; // On retire l'ancien sommet de la liste.

		for (int i = 0; i < 5; i++) // Initialisation du tableau des plus proches voisins
			V[i] = -1; // Pas de proche voisin au démarrage

		for (int j = 0; j < nr; j++) // Pour chaque sommet restant (rappel : on a retiré x)
		{
			y = L[j]; // Sommet actuel
			for (int k = 0; k < 5; k++) // On essaire de l'insérer dans les plus proches voisins
			{
				if (V[k] == -1 || instance.distances[x][y] < instance.distances[x][V[k]]) // Si la distance est plus courte, on insere le sommet
				{
					// décalage de tous les voisins plus grands sur la droite
					decalage_droite(V, k);
					decalage_droite(pV, k);
					V[k] = y; // insertion de l'élément choisi
					pV[k] = j;
				}
					
			}
		}

 		// Initialisation pour la boucle de choix du voisin
		int k = 0; 
		bool stop = false;

		// Boucle de choix du voisin
		while (!stop)
		{
			int r = rand() % 100;

			if (r < 80)
			{
				T[i] = V[k];
				Px = pV[k];
				stop = true;
			} else
			{
				k++;
				if (k > 6)
				{
					T[i] = V[4];
					Px = pV[4];
					stop = true;
				}
			}
			
		}
		nr--;
	}
}

/*
	Fonction qui permet de calculer le coût d'une tournée. Permet de débugger dans les opérateurs pour être sûr des changements qu'ils opèrent sur une tournée.
	entrees : instance, instance d'où la tournée est générée
			  tournee, tournée dont on veut calculer le coût
	sorties : coût de la tournée
*/
double calcul_cout(t_instance& instance, t_tournee& tournee)
{
	double dist =  0.0;
	for (int i = 0; i < tournee.nb_sommet -1; i++)
	{
		dist += instance.distances[tournee.sommets[i]][tournee.sommets[i+1]];
	}
	return dist / 1000 * instance.vehicles[tournee.type].cout_m + instance.vehicles[tournee.type].cout_f;
}

/*
	Opérateur 2OPT, qui se charge d'optimiser une solution. 2OPT essaye d'inverser 2 éléments d'une tournée et garde ce changement si il optimise la solution
	entrees : instance, instance de la solution
			  sol, solution (contenant les tournées)
	sorties : booléen signifiant le succès ou l'echec de l'opérateur (utile pour choisir les opérateurs dans la recherche)
*/
bool opt(t_instance& instance, t_solution & sol)
{
	for (int i = 0; i < sol.nb_tournee; ++i) // Pour chaque tournée
	{
		for (int j = 1; j < sol.tournees[i].nb_sommet - 2; ++j) // Pour chaque sommet de la tournee (sauf depart et arriver : depot)
		{
			for (int k = j + 1; k < sol.tournees[i].nb_sommet - 1; ++k)
			{
				// Comme on travaille à l'intérieur d'une tournée, pas besoin de vérifier la charge du transport.
				// On note mx le coût en moins lors de l'inversion du trajet x.
				// On note px le coût supplémentaire lors de l'inversion du trajet x.

				t_tournee& tournee = sol.tournees[i];
				double mx = instance.distances[tournee.sommets[j - 1]][tournee.sommets[j]] + instance.distances[tournee.sommets[k]][tournee.sommets[k + 1]];
				double px = instance.distances[tournee.sommets[j - 1]][tournee.sommets[k]] + instance.distances[tournee.sommets[j]][tournee.sommets[k + 1]];
				if (mx > px) // Si le changement est avantageux
				{
					double t = 0;
					double gain = (mx - px) / 1000 * instance.vehicles[tournee.type].cout_m;

					// On fait l'échange.
					for (int q = 0; q <= (k-j)/ 2; ++q)
					{	
						int tmp = tournee.sommets[j+q];
						tournee.sommets[j + q] = tournee.sommets[k - q];
						tournee.sommets[k - q] = tmp;
					}
					tournee.cout -= gain;
					sol.cout_total -= gain;
					return true; // On remonte le succés, et on arrete le traitement.
				}
			}
		}
	}
	return false;
}

/*
	Opérateur d'insertion, qui se charge d'optimiser une solution. Il essaye de retirer un élément d'une tournée pour l'insérer dans une autre et garde ce changement si il optimise la solution
	entrees : instance, instance de la solution
			  sol, solution (contenant les tournées)
	sorties : booléen signifiant le succès ou l'echec de l'opérateur (utile pour choisir les opérateurs dans la recherche)
*/
bool opt_insertion(t_instance& instance, t_solution& sol)
{
	for (int i = 0; i < sol.nb_tournee; ++i) // Liste où on prend le sommet
	{
		t_tournee& t1 = sol.tournees[i];
		for (int j = 0; j < sol.nb_tournee; ++j) // Liste où on insère
		{
			if (i != j)
			{
				t_tournee& t2 = sol.tournees[j];
				for (int x = 1; x < t1.nb_sommet - 1; ++x) // On evite le depot.
				{
					// T[x] est le sommet à insérer.
					for (int y = 0; y < t2.nb_sommet - 1; ++y)
					{
						// T[y] : le prec de là où on insère 	
						double distance_t1 = t1.distance - instance.distances[t1.sommets[x - 1]][t1.sommets[x]] - instance.distances[t1.sommets[x]][t1.sommets[x + 1]] + instance.distances[t1.sommets[x - 1]][t1.sommets[x + 1]];
						double distance_t2 = t2.distance - instance.distances[t2.sommets[y]][t2.sommets[y + 1]] + instance.distances[t2.sommets[y]][t1.sommets[x]] + instance.distances[t1.sommets[x]][t2.sommets[y + 1]];
					
						double volume_t1 = t1.valeur - instance.quantite[t1.sommets[x]];
						double volume_t2 = t2.valeur +  instance.quantite[t1.sommets[x]];

						if (volume_t2 <= instance.vehicles[t2.type].quantite) // L'insertion est faisable
						{
							if (t1.nb_sommet == 3) // On retire le dernier sommet
							{
								double cout2 = distance_t2 * instance.vehicles[t2.type].cout_m / 1000 + instance.vehicles[t2.type].cout_f;

								if (cout2 < t1.cout + t2.cout) // Insertion rentable
								{
									for (int a = t2.nb_sommet; a > y; --a)
										t2.sommets[a + 1] = t2.sommets[a];
									t2.sommets[y + 1] = t1.sommets[x];
									t2.nb_sommet++;
									// Il faut supprimer la tournée T1.

									memcpy(sol.tournees + i, sol.tournees + i + 1, sizeof(t_tournee) * (sol.nb_tournee - i));
									sol.nb_tournee--;

									return true;
								}
							}
							else if (distance_t1 + distance_t2 < t1.distance + t2.distance) // Elle est rentable
							{
								int sommet = t1.sommets[x];

								for (int a = t2.nb_sommet; a > y; --a)
									t2.sommets[a + 1] = t2.sommets[a];

								for (int a = x; a < t1.nb_sommet; ++a)
									t1.sommets[a] = t1.sommets[a + 1];

								t1.nb_sommet--;
								t2.nb_sommet++;
								t2.sommets[y + 1] = sommet;

								t1.distance = distance_t1;
								t2.distance = distance_t2;
								double cout1 = distance_t1 * instance.vehicles[t1.type].cout_m / 1000 + instance.vehicles[t1.type].cout_f;
								double cout2 = distance_t2 * instance.vehicles[t2.type].cout_m / 1000 + instance.vehicles[t2.type].cout_f;

								sol.cout_total -= (t1.cout + t2.cout);
								sol.cout_total += (cout1 + cout2);

								t1.cout = cout1;
								t2.cout = cout2;

								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

/*
	Opérateur 2OPT inter tournées, qui se charge d'optimiser une solution. Il essaye de prendre le début d'une tournée et de mettre la fin d'une autre et garde ce changement si il optimise la solution
	entrees : instance, instance de la solution
			  sol, solution (contenant les tournées)
	sorties : booléen signifiant le succès ou l'echec de l'opérateur (utile pour choisir les opérateurs dans la recherche)
*/
bool opt_inter_tournees(t_instance& instance, t_solution& sol)
{
	for (int i = 0; i < sol.nb_tournee - 1; ++i)
	{
		t_tournee& t1 = sol.tournees[i];
		double cout_m_t1 = instance.vehicles[t1.type].cout_m / 1000;
		double cout_f_t1 = instance.vehicles[t1.type].cout_f;
		for (int j = i + 1; j < sol.nb_tournee; ++j)
		{
			t_tournee& t2 = sol.tournees[j];
			double cout_m_t2 = instance.vehicles[t2.type].cout_m / 1000;
			double cout_f_t2 = instance.vehicles[t2.type].cout_f;

			double distance_t1 = 0;
			int volume_t1 = 0;
			for (int x = 1; x < t1.nb_sommet - 2; ++x) // On parcourt tous les sommets sauf le depot (debut et fin)
			{
				int volume_t2 = 0;
				double distance_t2 = 0;
				volume_t1 += instance.quantite[t1.sommets[x]];
				distance_t1 += instance.distances[t1.sommets[x - 1]][t1.sommets[x]];

				for (int y = 1; y < t2.nb_sommet - 2; ++y) // Idem
				{
					volume_t2 += instance.quantite[t2.sommets[y]];
					distance_t2 += instance.distances[t2.sommets[y - 1]][t2.sommets[y]];

					double distance_t2_t1 = instance.distances[t2.sommets[y]][t1.sommets[x + 1]];
					double distance_t1_t2 = instance.distances[t1.sommets[x]][t2.sommets[y + 1]];

					double distance_fin_t1 = t1.distance - distance_t1; // - instance.distances[t1.sommets[x]][t1.sommets[x + 1]];
				    double distance_fin_t2 = t2.distance - distance_t2; // - instance.distances[t2.sommets[y]][t2.sommets[y + 1]];

					double nouveau_cout_t1 = (distance_t1 + distance_t1_t2 + distance_fin_t2) * cout_m_t1 + cout_f_t1;
					double nouveau_cout_t2 = (distance_t2 + distance_t2_t1 + distance_fin_t1) * cout_m_t2 + cout_f_t2;

					int v1_total = volume_t1 + t2.valeur - volume_t2;
					int v2_total = volume_t2 + t1.valeur - volume_t1;

					if (v1_total <= instance.vehicles[t1.type].quantite)
					{
						if ( v2_total <= instance.vehicles[t2.type].quantite) // Vérification des volumes
						{
							if (nouveau_cout_t1 + nouveau_cout_t2 + 10 < t1.cout + t2.cout) // Le changement est avantageux
							{
								double oldc = t2.cout;
								double c1 = calcul_cout(instance, t2);

								// Création des bonnes listes de sommets
								int tmp[nb_max_sommets_par_tournee];
								memcpy(tmp, t1.sommets, t1.nb_sommet * sizeof(int));
								memcpy(t1.sommets + x + 1, t2.sommets + y + 1, (30) * sizeof(int));
								memcpy(t2.sommets + y + 1, tmp + x + 1, (30) * sizeof(int));

								// Modification des couts, quantites et nombre de sommets
								t1.valeur = v1_total;
								t2.valeur = v2_total;

								int tmpn = t1.nb_sommet;
								t1.nb_sommet = x + t2.nb_sommet - y;
								t2.nb_sommet = y + tmpn - x;

								sol.cout_total -= (t1.cout + t2.cout) - (nouveau_cout_t1 + nouveau_cout_t2);

								t1.cout = nouveau_cout_t1;
								t1.distance = distance_t1 + distance_t1_t2 + distance_fin_t2;
								t2.cout = nouveau_cout_t2;
								t2.distance = distance_t2 + distance_t2_t1 + distance_fin_t1;

								// On sort de l'opérateur en indiquand un succés.
								return true;
							}
						} else
						{
							break;
						}
					}
				}
			}
		}
	}
	return false;
}

/*
	Recherche GRASP qui se charge d'éxécuter un certain nombre de fois les opérateurs 2OPT, 2OPT inter tournées et insertion afin d'améliorer au maximum une solution.
		Le choix de l'opérateur dans une itération se fait aléatoirement. Plus un opérateur réussi, plus la probabilité de le faire augmente et inversement.
	entrees : instance, instance de la solution
			  sol, solution (contenant les tournées)
*/
void grasp(t_instance& instance, t_solution& sol)
{
	constexpr unsigned int gain = 1000 / 50;
	unsigned int p1 = 333;
	unsigned int p2 = 333;
	unsigned int p3 = 334;
	unsigned int total = p1 + p2 + p3;
	int r;

	for (int i = 0; i < 30; ++i)
	{
		r = rand() % total; // génération d'un nombre aléatoire 
		
		// Sélection de l'opérateur aléatoirement, avec variation des probabilités par les résultats de chaque opéarateur.
		if (r < p1)
		{
			if (opt_insertion(instance, sol)) p1 += gain;
			else p1 -= gain;			
		} 
		else if (r < p1 + p2)
		{
			if (opt(instance, sol)) p2 += gain;
			else p2 -= gain;
		} 
		else
		{
			if (opt_inter_tournees(instance, sol)) p3 += gain;
			else p3 -= gain; 
		}
		
		// Gestion des bornes des probabilités
		total = p1 + p2 + p3;
		if (((float) p1 / (float) total) > 0.8) p1 -= gain;
		if (((float) p2 / (float) total) > 0.8) p2 -= gain;
		if (((float) p3 / (float) total) > 0.8) p3 -= gain;
		if (((float) p1 / (float) total) < 0.2) p1 += gain;
		if (((float) p2 / (float) total) < 0.2) p2 += gain;
		if (((float) p3 / (float) total) < 0.2) p3 += gain;
		total = p1 + p2 + p3;
	}
}

/*
	Fonction qui permet d'ajouter (ou non) un label dans une liste de label. Si le label est meilleur qu'un autre, il le remplace, si il est moins bon, on ne l'insère pas et si il n'est
		pas comparable aux labels de la liste, on l'insère.
	entrees : liste, liste de labels
			  label, label à insérer
*/
void ajouter_label(t_liste_label& liste, t_label& label)
{
	
	for (int i = 0; i < liste.nb_labels; i++)
	{
		int r = domine(label, liste.liste[i]);
		if (r == 1) // Le nouveau domine l'ancien.
		{
			liste.liste[i] = label;
			return;
		}
		else if (r == -1 || r == 2) // Celui de la liste dominait deja où ils sont égaux.
		{
			return;
		} 
	}

	if (liste.nb_labels < nb_max_labels)
	{
		liste.liste[liste.nb_labels] = label; // On ajoute le label a la liste
		liste.nb_labels++;
		return;
	}
	return;
}

/*
	Fonction qui permet d'obtenir toutes les tournées d'une solution avec un graphe généré par SPLIT.
	entrees : instance, instance de la solution
			  graph, graphe généré par SPLIT contenant tous les labels
	sorties : sol, solution (contenant les tournées)
*/
bool from_split_to_tournee(t_instance& instance, int * T, t_graphe_split& graph, t_solution& solution)
{
	int lvl = graph.nb_sommets - 1; // On part de la fin

	if (graph[lvl].nb_labels == 0) return false; // Si le split n'est pas parvenu à la fin.

	t_label * prec = &graph[lvl][0];
	for (int i = 1; i < graph[lvl].nb_labels; ++i)
		if (graph[lvl][i].cout < prec->cout)
			prec = &graph[lvl][i];

	int min_sommet, max_sommet = lvl;
	solution.cout_total = prec->cout;
	solution.nb_tournee = 0;

	// Tant qu'on n'est pas remonté à l'origine du graphe.
	while (max_sommet != 0)
	{
		// On passe d'un sommet à son prec, en récupérant les informations du label.
		// On crées en meme temps les tournées et on les ajoutes à la solution
		min_sommet = prec->noeud;
		solution.tournees[solution.nb_tournee].valeur = 0;

		solution.tournees[solution.nb_tournee].sommets[0] = 0;
		solution.tournees[solution.nb_tournee].sommets[max_sommet-min_sommet] = 0;

		for (int i = 1; i < max_sommet - min_sommet + 1; ++i)
		{
			solution.tournees[solution.nb_tournee].sommets[i] = T[i + min_sommet - 1];
			solution.tournees[solution.nb_tournee].valeur += instance.quantite[T[i + min_sommet - 1]];
		}

		solution.tournees[solution.nb_tournee].distance = 0;
		solution.tournees[solution.nb_tournee].nb_sommet = max_sommet - min_sommet + 2;
		for (int i = 1; i < solution.tournees[solution.nb_tournee].nb_sommet; ++i)
			solution.tournees[solution.nb_tournee].distance += instance.distances[solution.tournees[solution.nb_tournee].sommets[i - 1]][solution.tournees[solution.nb_tournee].sommets[i]];

		solution.tournees[solution.nb_tournee].type = prec->vehicule;
		if (prec->prec != nullptr)
			solution.tournees[solution.nb_tournee].cout = prec->cout - prec->prec->cout;
		(solution.nb_tournee)++;
		max_sommet = min_sommet;
		prec = prec->prec;
	}

	return true; // Le split a reussi à faire une découpe de la tournée géante.
}

/*
	Fonction qui permet d'afficher un label sur la sortie standard (pour le débug)
	entrees : lab, label à afficher
*/
void afficher_label(t_label const & lab)
{
	std::cout << "Cout : " << std::setw(3) << lab.cout << " Noeud : " << lab.noeud << " Véhicule : " << lab.vehicule << " Ressources : [";
	std::cout << std::setw(2) << lab.ressources[0];
	for (int i = 1; i < lab.nb_ressources; ++i)
	{
		std::cout << ", " << std::setw(2) << lab.ressources[i];
	}
	std::cout << "]" << std::endl;
}

/*
	Fonction SPLIT, qui permet de créer un graphe avec des labels pour générer une solution à partir d'une instance d'un problème et d'un tour géant.
	entrees : instance, instance de la solution
			  T, tour géant
	sorties : graph, graphe permettant de générer une solution
*/
void split(t_instance& instance, int * T, t_graphe_split& graph)
{
	// Init graph
	graph.nb_sommets = instance.nb_sommets + 1;

	// Init du premier label du sommet 0
	graph[0][0].nb_ressources = instance.nb_types_vehicules;
	for (int i = 0; i < instance.nb_types_vehicules; i++) // On insere le nombre de vehicule de chaque type dans le premier label
		graph[0][0].ressources[i] = instance.vehicles[i].nb_vehicules;
	graph[0][0].cout = 0; // Le premier label a un cout de 0
	graph[0][0].prec = nullptr;
	graph[0].nb_labels = 1; // Il n'y a qu'un seul label
	
	//afficher_label(graph[0][0]);

	for (int i = 0; i < instance.nb_sommets; i++)
	{
		for (int j = i + 1; j < instance.nb_sommets; j++)
		{
			// Dans le graphe généré, la tournee actuelle (représentée par i et j avec la tournée géante) donne:
			// i est l'indice dans t_graph_split du sommet de départ
			// j+1 est l'indice dans t_graph_split du sommet d'arrivé

			// Calcul du volume total de la tournee
			int volume_tournee = 0;
			for (int k = i; k <= j; k++)
				volume_tournee += instance.quantite[T[k]];

			for (int k = 0; k < graph[i].nb_labels; k++) // Pour chaque labels
			{
				for (int p = 0; p < instance.nb_types_vehicules; p++) // Pour chaque camions dans le label
				{
					// Est-ce que le vehicule peut transporter le volume de la tournee
					if (volume_tournee <= instance.vehicles[p].quantite && graph[i][k].ressources[p] > 0)
					{
						// Calcul de la distance de la tournee
						double distance = instance.distances[0][T[i]];
						distance += instance.distances[T[j]][0];

						for (int x = i; x < j; x++)
							distance += instance.distances[T[x]][T[x + 1]];
						
						t_label nouveau_label = graph[i][k]; // On copie le label du sommet de départ
						nouveau_label.cout += (double)(distance / 1000 * instance.vehicles[p].cout_m + instance.vehicles[p].cout_f); // On rajoute le cout de la tournee
						nouveau_label.ressources[p] -= 1; // On enleve un vehicule
						nouveau_label.prec = &graph[i][k];
						nouveau_label.noeud = i;
						nouveau_label.vehicule = p;
						ajouter_label(graph[j+1], nouveau_label); // On ajoute (ou pas) le nouveau label créé à la liste de label du sommet d'arrivé
					}
				}
			}
		}
	}
}

/*
	Fonction qui permet de savoir si tous les éléments d'un tableau sont supérieur ou égaux à un éléments d'autre tableau de même taille
		Fonction servant à la fonction domine
	entrees : l, tableau d'entiers
			  r, tableau d'entiers
			  nb, nombre d'éléments dans le tableau
	sorties : booléen, vrai si tous les éléments de l sont supérieur ou égaux au éléments de r, faux sinon
*/
bool resource_inf(int const * l, int const * r, int nb)
{
	bool res = true;
	for (int i = 0; i < nb; ++i)
		res &= l[i] >= r[i];
	return res;
}

/*
	Fonction servant à l'insertion d'un label dans une liste de labels pour savoir si un label domine un autre
	entrees : P1, P2, deux labels à comparer
	sorties : 1 si P1 domine P2
			  0 si on ne peut pas determiner le dominant
			  1 si P2 domine P1
 			  2 si identique
*/
int domine(t_label const & P1, t_label const & P2)
{
	int res = 0;

	if (P1.cout < P2.cout)
		if (resource_inf(P1.ressources, P2.ressources, P1.nb_ressources)) res = 1;
		else res = 0;
	else if (P1.cout == P2.cout)
	{
		bool identique = true;
		for (int i = 0; i < P1.nb_ressources && res <= 1; ++i)
		{
			if (res == 0)
			{
				if (P1.ressources[i] > P2.ressources[i]) 
				{
					res = 1;
					identique = false;
				}
				else if (P1.ressources[i] < P2.ressources[i])
				{
					res = -1;
					identique = false;
				}
			} 
			else if (res == 1 && P1.ressources[i] < P2.ressources[i]) res = 2;
			else if (res == -1 && P1.ressources[i] > P2.ressources[i]) res = 3;
		}
		if (res == 2 || res == 3) res = 0;
		if (identique) return res = 2;
	} 
	else
		if (resource_inf(P1.ressources, P2.ressources, P1.nb_ressources)) res = -1;
		else res = 0;
	
	return res;
}

/*
	Fonction qui permet de tester la fonction de dominance
*/
void teste_de_dominance()
{
	t_label label1, label2;

	label1.cout = 1;
	label2.cout = 0;

	label1.nb_ressources = 3;
	label2.nb_ressources = 3;

	label1.ressources[0] = 0;
	label2.ressources[0] = 0;

	label1.ressources[0] = 0;
	label2.ressources[0] = 0;

	label1.ressources[0] = 0;
	label2.ressources[0] = 0;

	std::cout << "L1 = L2 : " << domine(label1, label2) << std::endl;

	label1.ressources[0] = 1;
	std::cout << "L1 > L2 : " << domine(label1, label2) << std::endl;

	label1.ressources[0] = 0;
	label2.ressources[0] = 1;
	std::cout << "L1 < L2 : " << domine(label1, label2) << std::endl;

	label1.ressources[0] = 0;
	label2.ressources[0] = 1;
	label1.ressources[1] = 1;
	label2.ressources[1] = 0;
	std::cout << "L1 != L2 : " << domine(label1, label2) << std::endl;
}

/*
	Fonction qsol, solution à afficher
*/
void afficher_solution(t_solution& sol)
{
	int taille_tournee = std::to_string(sol.nb_tournee).length();
	int taille_cout = std::to_string(sol.tournees[0].cout).length();
	int taille_sommet = std::to_string(sol.tournees[0].nb_sommet).length();
	int taille_valeur = std::to_string(sol.tournees[0].valeur).length();

	for (int i = 1; i < sol.nb_tournee; ++i)
	{
		if (taille_cout < std::to_string(sol.tournees[i].cout).length())
			taille_cout = std::to_string(sol.tournees[i].cout).length();
		if (taille_sommet < std::to_string(sol.tournees[i].nb_sommet).length())
			taille_sommet = std::to_string(sol.tournees[i].nb_sommet).length();
		if (taille_valeur < std::to_string(sol.tournees[i].valeur).length())
			taille_valeur = std::to_string(sol.tournees[i].valeur).length();
	}

	std::cout << "Solution avec un coût de : " << sol.cout_total << '.' << std::endl;
	std::cout << "Utilisation de " << sol.nb_tournee << " tournées." << std::endl;

	for (int i = 0; i < sol.nb_tournee; ++i)
	{
		std::cout << "\tTournee " << std::setw(taille_tournee) << i << " : cout de " << std::setw(taille_cout) << sol.tournees[i].cout << " (" << std::setw(taille_valeur) << sol.tournees[i].valeur << "kg - " << (int) sol.tournees[i].distance << "m)";
		std::cout << " pour " << std::setw(taille_sommet) << sol.tournees[i].nb_sommet - 2 << " sommets traversés, avec un véhicule de type " << sol.tournees[i].type << " : ";
		for (int j = 0; j < sol.tournees[i].nb_sommet; ++j)
		{
			std::cout << sol.tournees[i].sommets[j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}

inline t_liste_label& t_graphe_split::operator[](int i)
{
	return liste[i];
}


inline t_label& t_liste_label::operator[](int i)
{
	return liste[i];
}