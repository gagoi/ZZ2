/**
 * @file job_shop.cpp
 * @author Jérémy ZANGLA (zangla.jeremy@gmail.com)
 * @author Mathieu ARQUILLIERE (zangla.jeremy@gmail.com)
 * @brief Librairie permettant le calcul d'ordonnancement selon la méthode de Bierwirth
 * @version 1.0
 * @date 2019-10-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "job_shop.h"

/**
 * @brief Fonction de lecture du fichier d'entrée contenant le temps de traitement de chaque pièce sur chaque machine.
 * 
 * @param nom_fichier Nom du fichier à lire
 * @param instance Instance où on stockera les informations lues
 */
void lire_fichier(std::string nom_fichier, t_instance& instance)
{
	std::ifstream fichier(nom_fichier);

	if (fichier)
	{
		// Récupération des paramètres de l'instance
		fichier >> instance.nb_pieces;
		fichier >> instance.nb_machines;
	
		// Chargement des taches
		for (int i = 0; i < instance.nb_pieces; i++)
		{
			for (int j = 0; j < instance.nb_machines; j++)
			{
				fichier >> instance.sequences[i][j];
				instance.sequences[i][j]++;
				fichier >> instance.durees[i][j];
			}
		}

		// Initialisation de notre table de hash
		for (size_t i = 0; i < max_hashs; i++)
			instance.hashs[i] = 0;
	}
}

/**
 * @brief Fonction générant un vecteur de Bierwirth.
 * 
 * @param solution Solution qui contiendra le vecteur de Bierwirth généré
 * @param instance Instance contenant les informations sur le calcul à faire
 */
void generer_vb(t_solution& solution,const t_instance& instance)
{
	// Initialisation
	int i = 0;
	int max = instance.nb_pieces * instance.nb_machines;
	int tab_m_limit = instance.nb_pieces;
	int tab_m_name[max_piece];
	int tab_m_count[max_piece];

	for (int i = 0; i < instance.nb_pieces; i++)
	{
		tab_m_name[i] = i;
		tab_m_count[i] = instance.nb_machines;
	}

	// Remplissage du vecteur de bierwirth
	solution.taille = max;
    while (i < max)
	{
		int nb_rand = std::rand() % tab_m_limit;
		int piece = tab_m_name[nb_rand];

		solution.vb[i] = piece + 1;
		tab_m_count[nb_rand]--;

		if (tab_m_count[nb_rand] == 0)
		{
			// La ligne tirée au hasard n'a plus de machine à mettre dans le vecteur
			// On copie la derniere ligne a la place de celle-ci et on réduit de 1 la taille
			tab_m_name[nb_rand] = tab_m_name[tab_m_limit - 1];
			tab_m_count[nb_rand] = tab_m_count[tab_m_limit - 1];

			tab_m_limit--;
		}
		i++;
	}
}

/**
 * @brief Initialisation de la solution pour effectuer le calcul.
 * 
 * @param solution Solution du calcul à initialiser
 * @param instance Instance contenant la configuration du problème, nécessaire pour créer des tableaux d'accès rapides aux informations pour le calul
 */
void init_evaluer(t_solution & solution, const t_instance & instance)
{
	solution.taille = instance.nb_machines * instance.nb_pieces;

	// Init de N
	for (int i = 0; i < max_machine; i++)
		solution.N[i] = 0;

	for (size_t i = 0; i < max_piece; i++)
	{
		for (size_t j = 0; j < max_machine; j++)
		{
			solution.T[i][j] = -1;
		}
	}
	// Init de T
	for (int i = 0; i < instance.nb_machines*instance.nb_pieces; i++)
	{
		solution.T[i / instance.nb_machines + 1][i % instance.nb_machines + 1] = i + 1;
	}
	

	// Init de t
	for (int i = 0; i < instance.nb_machines * instance.nb_pieces; i++)
			solution.t[i + 1] = i / instance.nb_machines + 1;
			
	// Init de t2
	for (int i = 0; i < instance.nb_machines * instance.nb_pieces; i++)
		solution.t2[i + 1] = i % instance.nb_machines + 1;

	// Init de Pp
	for (int i = 0; i < max_machine * max_piece; i++)
		solution.Pp[i] = -1;
	for (int i = 0; i < instance.nb_pieces; i++)
		for (int j = 0; j < instance.nb_machines; j++)
			solution.Pp[1 + j + i * instance.nb_machines] = instance.durees[i][j];

	// Init de MP
	for (int i = 0; i < max_machine; i++)
		solution.MP[i] = 0;

	// Init de Mm
	for (int i = 0; i < max_machine * max_piece; i++)
		solution.Mm[i] = -1;
	for (int i = 0; i < instance.nb_pieces; i++)
		for (int j = 0; j < instance.nb_machines; j++)
			solution.Mm[1 + j + i * instance.nb_machines] = instance.sequences[i][j];

	// Init de st
	for (int i = 0; i < max_machine * max_piece; i++)
		solution.st[i] = 0;

	// Init de pred
	for (int i = 0; i < max_machine * max_piece; i++)
		solution.Pred[i] = -1;

	// Init du temps total
	solution.temps_total = 0;
}

/**
 * @brief Evalutation de la solution
 * 
 * Calcul les temps de départ de chaque tâche, ainsi que les précédences à partir du vecteur de Bierwirth choisi.
 * 
 * @param solution Solution contenant le vecteur, les précédences, 
 * les temps de départ des tâches ainsi que les variables nécessaires à l'algorithme.
 */
void evaluer(t_solution& solution)
{
	int pos = -1;	// Position actuel dans le graphe (sur le chemin limitant).
	int prec = -1; 	// Position précédant pos.

	// Pour chaque élément du vecteur de Bierwirth
	for (int i = 0; i < solution.taille; i++)
	{
		int j = solution.vb[i]; // On sélectionne quel job on traite
		solution.N[j]++; // On incrémente le compteur d'utilisation de ce job
		pos = solution.T[j][solution.N[j]]; // On sélectionne la tache correspondante
	
		// Si on avait déjà travailler avec ce job
		if (solution.N[j] > 1) 
		{
			// On trouve l'élément précédent
			prec = pos - 1;

			// Si on doit attendre que la tache précédente doit finir
			if (solution.st[prec] + solution.Pp[prec] > solution.st[pos])
			{
				// On indique que le temps de départ est après la fin de la tâche précédente
				solution.st[pos] = solution.st[prec] + solution.Pp[prec]; 
				// On indique que prec est notre précédent.
				solution.Pred[pos] = prec; 
			}
		}

		int machine = solution.Mm[pos]; // On sélectionne la machine utilisée par la tâche
		if (solution.MP[machine] != 0) // Si on l'a déjà utilisée
		{
			prec = solution.MP[machine]; // On accède à la tâche précédente sur la machine

			// Si il faut attendre que la machine soit libre
			if (solution.st[prec] + solution.Pp[prec] > solution.st[pos]) 
			{
				// On indique que le temps de départ est après la fin de l'utilisation de la machine
				solution.st[pos] = solution.st[prec] + solution.Pp[prec]; 
				// On indique que prec est notre précédent
				solution.Pred[pos] = prec; 
			}
		}
		solution.MP[machine] = pos; // On retient quelle est la dernière tâche passée sur la machine
	}

	// Calcul du temps total de la solution finale
	for (int i = 1; i <= solution.taille; ++i)
		if (solution.temps_total < solution.st[i] + solution.Pp[i]) solution.temps_total = solution.st[i] + solution.Pp[i];
}
/**
 * @brief Amélioration d'une solution existante via des changements sur le chemin critique.
 * 
 * @param solution Solution contenant le vecteur, les précédences, les temps de départ des tâches ainsi que les variables nécessaires à l'algorithme.
 * @param instance Instance contenant les informations sur le problème à résoudre.
 */
void recherche_locale(t_solution & solution, const t_instance & instance)
{
	const int itermax = 15;		// Nombre d'itérations maximum que l'on s'autorise pour la recherche locale
	t_solution sp;				// Solution utilisée pour sauvegarder la solution précédente pendant une nouvelle évaluation
	int iter = 0;				// Nombre d'itérations effectuées
	int i = 1; 					// Dernier élément du chemin limitant

	// Recherche de l'élément commençant le plus tard (i)
	for (int k = 2; k <= solution.taille; ++k)
		if (solution.st[i] + solution.Pp[i] < solution.st[k] + solution.Pp[k]) i = k;

	int j = solution.Pred[i]; // Element précédent l'élément limitant

	
	// Tant qu'on a pas finis de parcourir le chemin limitant, et qu'on n'a pas atteint le nombre d'itérations maximum
  	while (j != -1 && ++iter < itermax)
	{
		// Si i et j sont sur la même machine
		if (solution.Mm[i] == solution.Mm[j])
		{
			// On recherche quelles tâches correspondent à i et j
			int pi = 0, pj = 0;

			for (int ii = 0; ii != solution.t2[i]; ++pi)
				if (solution.vb[pi] == solution.t[i])
					++ii;
			for (int jj = 0; jj != solution.t2[j]; ++pj)
				if (solution.vb[pj] == solution.t[j])
					++jj;
			pi--;
			pj--;

			// On se prépare à une nouvelle évaluation
			init_evaluer(sp, instance);
			sp.taille = solution.taille;

			// Copie du vecteur de la solution précédente dans sp
			memcpy(&sp.vb, &solution.vb, sizeof(int) * solution.taille); 
			// Inversion des deux éléments sélectionnés (correspondants à i et j)
			sp.vb[pi] = solution.vb[pj];
			sp.vb[pj] = solution.vb[pi];

			// Evaluation de la solution
			evaluer(sp);

			// La nouvelle solution est plus rapide
			if (solution.temps_total > sp.temps_total) 
			{	
				// On remplace l'ancienne solution
				memcpy(&solution, &sp, sizeof(t_solution));

				// On recherche de nouveau le dernier élément du chemin critique
				i = 1;
				for (int k = 1; k <= solution.taille; ++k)
					if (solution.st[i] + solution.Pp[i] < solution.st[k] + solution.Pp[k]) i = k;

				j = solution.Pred[i]; // Element précédent l'élément limitant
			} else // La solution n'est pas plus efficace
			{
				i = j; // On passe sur l'élément précédant.
				j = solution.Pred[i]; // Idem
			}
			
		} else // Les deux tâches ne sont pas sur la même machine
		{
			i = j; // On passe sur l'élément précédant.
			j = solution.Pred[i]; // Idem
		}
		
	}
}

/**
 * @brief Affiche une solution sur la sortie standard.
 * 
 * @param solution Solution contenant le vecteur, les précédences ainsi que les temps de départ et la durée des tâches.
 * @param instance Instance contenant les informations sur le problème.
 */
void afficher_solution(const t_solution& solution, const t_instance& instance)
{
	// Affiche le nombre de machine, le nombre de pièce et le temps de la solution
	std::cout << std::endl << "Nombre de machines : " << instance.nb_machines << std::endl << "Nombre de pièces : " << instance.nb_pieces << std::endl << "Temps total : " << solution.temps_total << std::endl << "Vecteur : ( ";
	

	// Affiche le vecteur de Bierwirth
	for (int i = 0; i < instance.nb_pieces * instance.nb_machines; ++i)
		std::cout << solution.vb[i] << " ";
	std::cout << ")" << std::endl << "Prédécesseurs :  ( ";

	// Affiche la liste des prédécesseurs
    for (int i = 1; i <= instance.nb_machines * instance.nb_pieces; ++i)
         printf("%2d ", solution.Pred[i]);
    std::cout << ")" << std::endl << "Starting times : ( ";

	// Affiche la liste des temps de départ
	for (int i = 1; i <= instance.nb_machines * instance.nb_pieces; ++i)
        printf("%2d ", solution.st[i]);
    std::cout << ")" << std::endl;

	// Recherche du dernier élément du chemin critique
	int i = 1;
	for (int k = 1; k <= solution.taille; ++k)
		if (solution.st[i] + solution.Pp[i] < solution.st[k] + solution.Pp[k]) 
			i = k;

	// Affichage du chemin critique
	std::cout << "Chemin limitant (ordre inverse) : ";
	while (solution.Pred[i] != -1)
	{
		std::cout << i << " <- ";
		i = solution.Pred[i];
	}
	std::cout << i << std::endl;

	// Création d'un diagramme de Gantt représentant la solution
	// Attention, il ne fonctionne pas si le nombre de tâches est trop important
	char** gantt = new char* [instance.nb_machines + 1];
	for (size_t i = 0; i < instance.nb_machines + 1; i++)
	{
		gantt[i] = new char[solution.temps_total];
	}
	// Initialisation de la matrice comme étant vide
	for (int i = 0; i <= instance.nb_machines; ++i)
		for (int j = 0; j < solution.temps_total; j++)
			gantt[i][j] = ' ';
	// Ajout de chaque tâche dans la matrice comme étant représentée par une lettre
	for (int i = 1; i <= solution.taille; i++)
		for (int j = solution.st[i]; j < solution.st[i] + solution.Pp[i]; ++j)
			gantt[solution.Mm[i]][j] = solution.t[i] + 'A';
	// Affichage de l'échelle
	for (int j = 0; j < solution.temps_total; ++j)
		printf("%4d|", j);
	std::cout << std::endl;
	// Affichage d'une ligne de séparation
	for (int j = 0; j < solution.temps_total; ++j)
		std::cout << "-----";
	std::cout << std::endl;
	// Affichage du diagramme de Gantt
	for (int i = 1; i <= instance.nb_machines; i++)
	{
		for (int j = 0; j < solution.temps_total; ++j)
			printf("   %1c|", gantt[i][j]);
		std::cout << std::endl;
	}

	for (size_t i = 0; i < instance.nb_machines + 1; i++)
	{
		delete[] gantt[i];
	}
	delete[] gantt;
}

/**
 * @brief Vérifie si une solution est possible
 * 
 * Pour faire la vérification, on vérifie simplement si chaque tâche commence bien après sa précédente.
 * 
 * @param solution Solution contenant le vecteur, les précédences ainsi que les temps de départ et la durée des tâches.
 * @return true La solution semble fonctionner.
 * @return false Il y a une erreur dans la solution.
 */
bool verifier_solution(const t_solution& solution)
{
	for (int i = 1; i <= solution.taille; ++i)
	{
		//std::cout << "i = " << i << std::endl;
		int j = i;
		int st = solution.st[j];
		while (solution.Pred[j] != -1)
		{
			j = solution.Pred[j];
			st -= solution.Pp[j];
			//std::cout << "  j = " << j << std::endl;
		}
		if (st != 0)
		{
			//std::cout << "st = " << st << std::endl;
			return false;
		}
	}

	return true;
}

/**
 * @brief Permet de calculer un identifiant de la solution.
 * 
 * Cette identifiant est considéré unique (il y a peu de probabilités d'avoir deux solutions différentes avec le même identifiant),
 * et est facile à comparer à un autre.
 * 
 * @param solution 
 * @return long Identifiant appelé hash.
 */
long calculer_hash(const t_solution& solution)
{
	long hash = 0;

	// On fait la somme des temps de départ élevés au carré.
	for (size_t i = 1; i <= solution.taille; i++)
	{
		hash += solution.st[i] * solution.st[i];
	}
	
	return hash % max_hashs;
}

/**
 * @brief Vérifie si l'on a deja traité une solution.
 * 
 * @param hash Hash de la solution à vérifier.
 * @param instance Instance à laquelle la solution répond.
 * @return true La solution correspondante au hash existe déja.
 * @return false La solution correspondante au hash n'existe pas encore.
 */
bool tester_double(long hash, const t_instance& instance)
{
	return instance.hashs[hash];
}

/**
 * @brief Exécution de l'algorithme GraspxEls pour le problème des JobShops.
 * 
 * @param solution Solution générée par la procédure.
 * @param instance Instance du problème à traiter.
 */
void grasp(t_solution& solution, t_instance& instance)
{
	const int max_iter = 100; 			// Nombre max d'itérations autorisées
	const int max_voisins = 5; 			// Nombre max de voisins générés à chaque itération 
	const int max_essais_voisins = 25;	// Nombre max de tentatives autorisées pour la génération des voisins
	long hash;							// Hash de la dernière solution crée.
	t_solution voisins[max_voisins];	// Tableau contenant les voisins de la solution crées.

	
	// Initialisation des paramètres et génération d'un premier vecteur
	init_evaluer(solution, instance);
	generer_vb(solution, instance);

	// Evaluation et amélioration de cette première solution
	evaluer(solution);
	recherche_locale(solution, instance);
	// On calcule le hash de la solution
	hash = calculer_hash(solution);

	// Pour chaque itération de l'algorithme
	for (size_t iter = 0; iter < max_iter; iter++)
	{	
		int meilleure_voisin = 0;		// Indice du meilleur voisin trouvé
		int nb_voisins_trouves = 0;		// Nombre de voisins trouvés à cette itération
		
		// Génération des voisins
		for (size_t i = 0; nb_voisins_trouves < max_voisins && i < max_essais_voisins; i++)
		{
			// Initialisation du voisin et copie du vecteur d'origine
			init_evaluer(voisins[nb_voisins_trouves], instance);
			memcpy(&(voisins[nb_voisins_trouves].vb), &(solution.vb), sizeof(int) * solution.taille); 

			// On trouve deux éléments du vecteur à échanger
			int pi = rand() % voisins[0].taille;
			int pj;
			// On s'assure que l'on échange bien deux éléments différents
			do
			{
				pj = rand() % solution.taille;
			} while (solution.vb[pi] == solution.vb[pj]);

			// Permutation de deux éléments pour créer le vecteur voisin
			voisins[nb_voisins_trouves].vb[pi] = solution.vb[pj];
			voisins[nb_voisins_trouves].vb[pj] = solution.vb[pi];


			// On évalue la solution
			evaluer(voisins[nb_voisins_trouves]);

			// On calcule le hash de la solution
			hash = calculer_hash(voisins[nb_voisins_trouves]);
			// Si la solution est nouvelle
			if (!tester_double(hash, instance))
			{
				// On retient son existence
				instance.hashs[hash] = 1;
				// On lance une recherche locale
				recherche_locale(voisins[nb_voisins_trouves], instance);

				// On garde le meilleur voisin
				if (voisins[meilleure_voisin].temps_total > voisins[nb_voisins_trouves].temps_total)
					meilleure_voisin = nb_voisins_trouves;
				// On incrémente le nombre de voisin trouvé
				nb_voisins_trouves++;
			}
		}
		// On a trouvé le meilleur voisin
		// On vérifie si c'est la meilleure solution trouvée.
		if (voisins[meilleure_voisin].temps_total < solution.temps_total)
			solution = voisins[meilleure_voisin];
	}
}