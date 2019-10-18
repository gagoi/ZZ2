#include "Liste.hpp"
Liste::Liste(): 
	_nbFormes(0)
{
}

void Liste::ajouterForme(Forme& f)
{
	if (_nbFormes < size)
	{
		_formes[_nbFormes] = &f;
		_nbFormes++;
	}
}

void Liste::afficher()
{
	for (unsigned int i = 0; i < _nbFormes; ++i)
	{
		std::cout << _formes[i]->toString() << std::endl;
	}	
}

Liste::~Liste()
{
}