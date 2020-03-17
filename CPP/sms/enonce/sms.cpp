#include "sms.hpp"

Telephone::Telephone(std::string num, Reseau * r):
	_r(r)
{
	setNumero(num);
}

Reseau::~Reseau()
{
	for (auto &&t : _tels)
	{
		delete t;
	}
	
}

std::string Reseau::lister() const
{
	std::ostringstream oss;
	for (auto &&t: _tels)
	{
		oss << t->getNumero() << '\n';
	}
	return oss.str();
}
Telephone& Reseau::trouveTel(std::string num) {
		auto t = _tels.begin(); 
		for (; t != _tels.end(); ++t) 
			if ((*t)->getNumero() == num) 
				break; 
		if (t != _tels.end()) 
			return **t;
		else 
			throw MauvaisNumero{};
	};


void Reseau::ajouter(std::string num)
{
	Telephone* pt = new Telephone(num, this);	

	auto t = _tels.begin();
	for (; t != _tels.end(); t++)
	{
		if (**t > *pt)
			break;
	}
	
	_tels.insert(t, pt);
}

int Message::nb_messages = 0;