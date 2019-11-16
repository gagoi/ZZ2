#include "RabbitSimulation.hpp"
#include <map>
#include <iomanip>

std::map<int, int> hist{};
std::map<int, int> hist2{};
int c = 0;

int main(int, char**)
{
	RabbitSimulation simu;


	Rabbit _r[10000];
	int i = 0;
	for (auto&& r : _r)
		if (r.get_death_week()/4.0 > 8) ++i;
	std::cout << i << std::endl;


	RabbitFemale * rf = new RabbitFemale[1000000];

    for(auto p : hist) {
        std::cout << std::setw(2)
                  << p.first << ' ' << std::string(p.second/2000, '*') << '\n';
    }

	int moy = 0;
	for(int i = 0; i < 1000000; ++i)
	{
		moy += rf[i].get_death_week();
		++hist2[rf[i].get_death_week()];
	}

	moy /= 1000000;

	std::cout << "Death moy : " << moy << std::endl;
	 for(auto p : hist2) {
        std::cout << std::setw(2)
                  << p.first << ' ' << std::string(p.second/10, '*') << '\n';
    }


	std::cout << "Oui : " << c << std::endl;

	return 0;
}