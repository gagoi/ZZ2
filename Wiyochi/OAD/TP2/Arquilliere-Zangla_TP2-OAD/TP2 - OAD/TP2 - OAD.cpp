#include <iostream>
#include "job_shop.h"
#include <cstring>

constexpr bool verbeux = false;


int main()
{

	int opt[] = { 666, 655, 597, 590, 593, 926, 890, 863, 951, 958, 1222, 1039, 1150, 1292, 1207, 945, 784, 848, 842, 902 };

	t_instance instance;
	t_solution solution;

	std::srand(std::time(nullptr));

	for (int i = 0; i < 20; ++i)
	{
		size_t j;
		double moy = 0;
		std::cout << "Instances n " << i + 1 << ":" << std::endl;
		char file_name[40];
		std::chrono::time_point<std::chrono::steady_clock> t1, t2;
		sprintf_s(file_name, "Instances/LA%.2d.txt", i + 1);
		lire_fichier(file_name, instance);
		for (j = 0; j < 20; ++j)
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			grasp(solution, instance);
			auto t2 = std::chrono::high_resolution_clock::now();
			moy += std::chrono::duration<double>(t2 - t1).count();
			std::cout << "\tTentative n " << j << ": " << std::chrono::duration<double>(t2 - t1).count() * 1000 << "ms" << std::endl;
			if (solution.temps_total == opt[i])
			{
				std::cout << "Solution optimale atteinte en " << j + 1 << " essais." << std::endl;
				++j;
				break;
			}
		}
		std::cout << "\tTemps moyen de traitement : " << moy * 1000 / j << "ms" << std::endl;

		if (verbeux)
			afficher_solution(solution, instance);
	}

	return 0;
}