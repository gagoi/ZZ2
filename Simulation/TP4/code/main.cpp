#include "RabbitSimulation.hpp"
#include <map>

int main(int, char**)
{
	RabbitSimulation simu(1000, 1000);
	RabbitSimulation simu2(1000, 1000);
	RabbitSimulation simu3(1000, 1000);
	RabbitSimulation simu4(1000, 1000);
	RabbitSimulation simu5(1000, 1000);

	simu.run(1000);
	simu2.run(1000);
	simu3.run(1000);
	simu4.run(1000);
	simu5.run(1000);

	return 0;
}