#ifndef CONTENEUR_HPP_
#define CONTENEUR_HPP_

#include <iostream>
#include <string>
#include <vector>

class Conteneur
{
private:
	double * _vals;
	int _capacity, _size;
	static const int default_capacity = 10;
public:
	Conteneur(int capacity = default_capacity);
	Conteneur(const Conteneur& c);
	~Conteneur();

	double& operator [] (const int & i);
	double& operator [] (const int & i) const;
	Conteneur& operator = (const Conteneur& c);

	friend std::ostream& operator << (std::ostream& os, const Conteneur& c);
	friend Conteneur operator + (const Conteneur& c1, const Conteneur& c2);

	void push_back(const double & f);

	int capacity() const;
	int size() const;
};

#endif
