#include "RabbitSimulation.hpp"

int main(int, char**)
{
	std::cout << "Début des Simulations" << std::endl;
	RabbitSimulation simu1(50, 1000, 1000);
	RabbitSimulation simu2(100, 1000, 1000);
	RabbitSimulation simu3(185, 1000, 1000);
	RabbitSimulation simu4(5, 1000, 1000);
	RabbitSimulation simu5(20, 1000, 1000);

	simu1.run(300);
	simu2.run(300);
	simu3.run(300);
	simu4.run(300);
	simu5.run(300);

	std::cout <<std::endl << "Fin des Simulations" << std::endl;
	return 0;
}