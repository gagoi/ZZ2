#ifndef CPP5__CHAINE_HPP
#define CPP5__CHAINE_HPP

#include <iostream>
#include <fstream>
#include <cstring>

class Chaine  {
private:
	int _capa;
	char * _tab;
public:
	Chaine();
	Chaine(const int taille);
	Chaine(const char * inCs);
	Chaine(const Chaine&);
	~Chaine();

	char * c_str() const;
	int getCapacite() const;
	void afficher(std::ostream & stream = std::cout) const;

	Chaine& operator=(const Chaine& c);
	char& operator[](const int & i);
	char& operator[](const int & i) const;
	friend std::ostream& operator<<(std::ostream& os, const Chaine& c);
	friend Chaine operator+(const Chaine& c1, const Chaine& c2);

	static void afficherParValeur(Chaine c);
	static void afficherParReference(Chaine& c);
};

#endif
