#include "RabbitSimulation.hpp"
#include <map>

int main(int, char**)
{
	RabbitSimulation simu(1000, 1000);

	simu.run(1000);

	return 0;
}