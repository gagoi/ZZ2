#include "hvrp.h"
#include "sstream"

int main()
{
	for (int i = 1; i < 5; ++i) // On ne traite que les 5 premières instances pour un soucis de temps d'exécution.
	{
		t_solution sol{};
		t_instance * instance = new t_instance{};
		t_graphe_split * graph = new t_graphe_split{};

		std::ostringstream oss; // Ouverture du fichier de l'instance
		if (i < 10) 
			oss << "HVRP_DLP_0" << i << ".txt";
		else
			oss << "HVRP_DLP_" << i << ".txt";

		if (charger_instance_distances(*instance, oss.str())) // Chargement du problème
		{
			int * tournee = new int[instance->nb_sommets]{};
			generer_tour_geant_ppv(*instance, tournee); // Génération de la tournée géante
			split(*instance, tournee, *graph); // Split de la tournée pour obtenir une solution initiale
			if(from_split_to_tournee(*instance, tournee, *graph, sol)) // Si on peut générér une solution à partir du split
			{
				std::cout << "Solution pour l'instance : " << i << " (plus proche voisin)." << std::endl;
				afficher_solution(sol); // Affichage de la solution initiale
				grasp(*instance, sol); // Amélioration de la solution
				std::cout << "Solution pour l'instance : " << i << " (plus proche voisin, puis optimisé)." << std::endl;
				afficher_solution(sol); // Affichage du résultat final
			}
			else
			{
				std::cout << "Aucun découpage trouvé pour la tournée " << i << " pour le plus proche voisin." << std::endl;
			}
			

			delete graph;
			graph = new t_graphe_split{};


			// Meme chose que précédemment mais on se laisse plusieurs essais pour obtenir la tournée géante.
			bool exit = false;
			int j = 0;
			do
			{
				generer_tour_geant_ppvr(*instance, tournee);
				split(*instance, tournee, *graph);
				exit = from_split_to_tournee(*instance, tournee, *graph, sol);
			} while (!exit && j++ < 20);
			
			if (exit) // Si une tournée à fonctionner on peut poursuivre
			{
				std::cout << "Solution pour l'instance : " << i << " (plus proche voisin randomisé)." << std::endl;
				afficher_solution(sol);
				grasp(*instance, sol);
				std::cout << "Solution pour l'instance : " << i << " (plus proche voisin randomisé, puis optimisé)." << std::endl;
				afficher_solution(sol);
			}
			else
			{
				std::cout << "Aucun découpage de la tournée " << i << " trouvé pour le plus proche voisin randomisé." << std::endl;
			}
			

			delete[] tournee;
		}
		delete instance;
		delete graph;
	}


	return 0;
}