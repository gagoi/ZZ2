#include "Conteneur.hpp"

Conteneur::Conteneur(int capacity):
	_capacity(capacity > 0 ? capacity : default_capacity), _size(0)
{
	_vals = new double[capacity];
}

Conteneur::Conteneur(const Conteneur& c):
	Conteneur(c.capacity())
{
	std::copy(c._vals, c._vals + c.size(), _vals);
	_size = c.size();
}

Conteneur::~Conteneur()
{
	delete [] _vals;
}

double& Conteneur::operator [] (const int & i)
{
	if (i < 0) throw std::out_of_range("Negativ index");
	else if (i > capacity()) throw std::out_of_range("Out of bounds");
	return _vals[i];
}

double& Conteneur::operator [] (const int & i) const
{
	return _vals[i];
}

Conteneur& Conteneur::operator = (const Conteneur& c)
{
	delete [] _vals;
	_capacity = c.capacity();
	_size = c.size();
	_vals = new double[c.size()];
	std::copy(c._vals, c._vals + c.size(), _vals);

	return *this;
}

std::ostream& operator << (std::ostream& os, const Conteneur& c)
{
	os << '[';
	for (int i = 0; i < c.size() - 1; ++i)
		os << c[i] << ',';
	os << c[c.size() - 1] << ']';
	return os;
}


Conteneur operator + (const Conteneur& c1, const Conteneur& c2)
{
	Conteneur c(c1.size() + c2.size());

	std::copy(c1._vals, c1._vals + c1.size(), c._vals);
	std::copy(c2._vals, c2._vals + c2.size(), c._vals + c1.size());
	c._size = c1.size() + c2.size();

	return c;
}

void Conteneur::push_back(const double & f)
{
	if (size() == capacity())
	{
		_capacity *= 2;
		double * f = new double[_capacity];
		std::copy(_vals, _vals + size(), f);

		delete[] _vals;
		_vals = f;
	}

	_vals[size()] = f;
	_size++;
}

int Conteneur::capacity() const
{
	return _capacity;
}

int Conteneur::size() const
{
	return _size;
}