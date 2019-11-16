#include "RabbitSimulation.hpp"

ushort RabbitSimulation::run_id = 0;
std::string RabbitSimulation::run_id_str = "0";

RabbitSimulation::RabbitSimulation(unsigned int nb_males_init, unsigned int nb_females_init):
 _run_id(run_id), _week(0), _nb_rabbits_total(nb_males_init + nb_females_init), _nb_males_total(nb_males_init), _nb_females_total(nb_females_init), _nb_childs_males_deaths(0), _nb_childs_females_deaths(0), _nb_adults_males_deaths(0),  _nb_adults_females_deaths(0)
{
	init_datas();
	
	std::cout << "Création de la simulation n°" << _run_id << ". Males : " << nb_males_init << ", Femelles : " << nb_females_init << std::endl;

	std::filesystem::create_directories(std::string("../Rapport/" + run_id_str).c_str());
	
	file1 = std::ofstream(std::string("../../Rapport/" + run_id_str + "/total_rabbits.rab", std::ios_base::app).c_str());
	file2 = std::ofstream(std::string("../../Rapport/" + run_id_str + "/total_females.rab", std::ios_base::app).c_str());
	file3 = std::ofstream(std::string("../../Rapport/" + run_id_str + "/total_males.rab", std::ios_base::app).c_str());

	for (unsigned int i = 0; i < nb_males_init; i++)
		_males.push_back(new Rabbit);
	for (unsigned int i = 0; i < nb_females_init; i++)
		_females.push_back(new RabbitFemale);

	run_id++;
	std::ostringstream oss;
	oss << run_id;
	run_id_str = oss.str();
}

RabbitSimulation::~RabbitSimulation()
{
	for (auto &&male : _males)
		delete male;
	
	for (auto &&female : _females)
		delete female;
}

void RabbitSimulation::run(unsigned int week)
{
	std::cout << "Travail sur la simulation n°" << _run_id << " pendant " << week << " semaines (à partir de " << _week << ")." << std::endl;

	for (unsigned int i = 0; i < week; ++i)
		grow();
}

unsigned int RabbitSimulation::get_childs_nb(std::list<Rabbit*> list)
{
	unsigned int i = 0;

	for (auto &&rabbit : list)
		if (rabbit->get_age() < rabbit->get_maturity())
			i++;
	
	return i;
}

unsigned int RabbitSimulation::get_childs_nb(std::list<RabbitFemale*> list)
{
	unsigned int i = 0;

	for (auto &&rabbit : list)
		if (rabbit->get_age() < rabbit->get_maturity())
			i++;
	
	return i;
}


void RabbitSimulation::grow()
{
	log_datas();
//	std::cout << "#" << _week << " : Nb males : " << _males.size() << '(' << get_childs_nb(_males) << ") ; Nb femelles : " << _females.size() << '(' << get_childs_nb(_females) << ')' << std::endl;
	births();
	die();
	for (auto &&rabbit : _males)
		rabbit->grow();
	for (auto &&rabbit : _females)
		rabbit->grow();
	
	_week++;
}

void RabbitSimulation::births()
{
	if (!_males.empty())
	{
		unsigned int old_males_count = _males.size();
		unsigned int old_females_count = _females.size();

		for (auto &&female : _females)
			female->give_birth(_week, _males, _females);

		unsigned int delta_males = _males.size() - old_males_count;
		unsigned int delta_females = _females.size() - old_females_count;

		_nb_males_total += delta_males;
		_nb_females_total += delta_females;
		_nb_rabbits_total += delta_males + delta_females;
	}
}

void RabbitSimulation::die()
{
	for (auto &&male : _males)
	{
		if (male->get_death_week() == _week)
		{
			if (male->get_age() < male->get_maturity())
				_nb_childs_males_deaths++;
			else
				_nb_adults_males_deaths++;

			delete male;
			male = nullptr;
		}
	}
	for (auto &&female : _females)
	{
		if (female->get_death_week() == _week)
		{
			if (female->get_age() < female->get_maturity())
				_nb_childs_females_deaths++;
			else
				_nb_adults_females_deaths++;

			delete female;
			female = nullptr;
		}
	}

	_males.remove(nullptr);
	_females.remove(nullptr);
}

void RabbitSimulation::init_datas()
{
	remove(std::string("../Rapport/" + run_id_str + "/total_rabbits.rab").c_str());
	remove(std::string("../Rapport/" + run_id_str + "/total_females.rab").c_str());
	remove(std::string("../Rapport/" + run_id_str + "/total_males.rab").c_str());
}

void RabbitSimulation::log_datas()
{
	if (_week % 16 == 0)
	{	
		file1 << _week << ' ' << _nb_rabbits_total << std::endl;
		file2 << _week << ' ' << _nb_females_total << std::endl;
		file3 << _week << ' ' << _nb_males_total << std::endl;

		file1.flush();
		file2.flush();
		file3.flush();
	}
}