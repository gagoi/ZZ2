#include "Mere.hpp"
#include "Fille.hpp"

#include <string>

int main(int, char**)
{
	Fille f(12);
	Fille f2(1);
	Fille f3(52);
	Mere m(12, std::string("dedefergrregregreg"));

	std::cout << m.getNom() << std::endl;

	m.afficher();

	Mere  *pm = new Mere(5, "mere_dyn");
Fille *pf = new Fille(4, "fille_dyn");
Mere  *pp = new Fille(3, "fille vue comme mere");
pm->afficher(); // affiche Mere
pf->afficher(); // affiche Fille
pp->afficher(); // affiche Fille
}