#include "Pile.hpp"

Pile::Pile(int capa):
	_capa(capa), _size(0)
{
	if (_capa > 0)
		_tab = new int [_capa];
	else 
		_tab = nullptr;
}

Pile::~Pile()
{
	if (_tab)
		delete[] _tab;
}


bool Pile::empty() const
{
	if (_capa <= 0) throw std::invalid_argument("Capacité de la pile négative ou nulle.");
	return _size == 0;
}

void Pile::push(const int i)
{
	if (_size == _capa) throw std::out_of_range("Dépassement de la taille max.");
	_tab[_size] = i;
	_size++;
}

int Pile::pop()
{
	if (_size <= 0) throw std::invalid_argument("Pile vide ou capacité nulle.");
	return _tab[--_size];
}

int Pile::top() const
{
	if (_size <= 0) throw std::invalid_argument("Pile vide ou capacité nulle.");
	return _tab[_size - 1];
}

int Pile::size() const
{
	return _size;
}