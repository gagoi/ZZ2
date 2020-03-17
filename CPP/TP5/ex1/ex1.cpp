#include <iostream>
#include <cstdlib>
#include "Forme.hpp"
#include "Cercle.hpp"

int nb_instance;

class Bavarde {
	private:
		int _i;
	public:
	Bavarde(int i=0):_i(i)
	{
		nb_instance++;
		std::cout << "Construction de " << _i << " instance : " << nb_instance << std::endl;
			}

	Bavarde(Bavarde const&):Bavarde(){
	}

	~Bavarde()
	{
		std::cout << "Tais-toi " << _i << " instance : " << nb_instance  << std::endl;
		nb_instance--;
	}
	int getI()
	{
		return _i;
	}

	void afficher()
	{
		std::cout << "Affichage de " << getI() << std::endl;
	}

};

void fonction(Bavarde b) {
  std::cout << "code de la fonction" << b.getI() << std::endl;
}

void test1(Bavarde b) {
  std::cout << "-- appel de fonction avec parametre objet et copie" << std::endl;
}

Bavarde test2a() {
  std::cout << "-- appel de fonction avec retour" << std::endl;
  return Bavarde();
}

Bavarde test2b() {
  Bavarde b;
  std::cout << "-- appel de fonction avec retour" << std::endl;
  return b;
}

void test3(Bavarde& b) {
  std::cout << "appel de fonction avec référence " << std::endl;
}

void test4(Bavarde *b) {
  std::cout << "appel de fonction avec un pointeur sur un objet"<< std::endl;
}
/*
int main(int, char**){

	Bavarde b1(36);
	test1(b1);

	Bavarde a = test2a();
	Bavarde c = test2b();

	test3(b1);
	test4(&b1);

	return 0;
}
*/
void afficher1(Forme f) {
   f.afficher();
}

void afficher2(Forme &f) {
   f.afficher();
}

void afficher3(Forme * f) {
   f->afficher();
}

int main(int, char**) {
   Cercle cercle;

   afficher1(cercle);
   afficher2(cercle);
   afficher2(&cercle);

   return 0;
}