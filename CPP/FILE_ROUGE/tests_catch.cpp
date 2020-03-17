// Le #define suivant permet de creer automatiquement une fonction main()
#define CATCH_CONFIG_MAIN  

#include "catch.hpp"

#include <fstream>
#include <iostream>

#include "Point.hpp"
#include "Cercle.hpp"
#include "Rectangle.hpp"
#include "Groupe.hpp"

// NOTE : ce test utilise des enum "class"
// il faut donc utiliser un compilateur g++ >= 6.1
// ou activer l'option c++11 du compilateur
// -std=c++11 ou -std=c++0x sur les tres vieux compilateurs

// Les tests ne sont pas exhaustifs, loin de là

TEST_CASE("Instanciation", "[Point]") {
	
	Point p1;
	REQUIRE(p1.getX() == 0);
	REQUIRE(p1.getY() == 0);
	
    p1.setX(11);
    p1.setY(21);

    REQUIRE(p1.getX() == 11);
	REQUIRE(p1.getY() == 21);

	Point p2(12, 22);

	REQUIRE(p2.getX() == 12);
	REQUIRE(p2.getY() ==  22);  // :-)

}


TEST_CASE("Origine", "[Point]") {
	REQUIRE(ORIGINE.getX() == 0);
	REQUIRE(ORIGINE.getY() == 0);
}

/*

TEST_CASE("Compteur", "[Forme]") {
   // Pour être correct, ce test doit etre le premier sur Forme
   REQUIRE(0 == Forme::prochainId());
   Forme f1;
   REQUIRE(0 == f1.getId());
   REQUIRE(1 ==  Forme::prochainId());	
   // Verification que la valeur n'est pas decrementee accidentellement.
   Forme *p = new Forme;
   REQUIRE(1 == p->getId());
   delete p;
   REQUIRE(2 == Forme::prochainId());	
}



TEST_CASE("Instanciation1", "[Forme]") {
	Forme f1;
	REQUIRE(f1.getPoint().getX() == 0);
	REQUIRE(f1.getPoint().getY() == 0);
	REQUIRE(f1.getCouleur() ==  COULEURS::BLEU);
}



TEST_CASE("Instanciation2", "[Forme]") {
	Forme f2;
	
	f2.setX(15);
	f2.setY(25);
	f2.setCouleur(COULEURS::VERT);
	REQUIRE (f2.getPoint().getX() == 15);
	REQUIRE (f2.getPoint().getY() == 25);
	REQUIRE (f2.getCouleur() == COULEURS::VERT);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::ROUGE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::JAUNE);
}



TEST_CASE("Instanciation3", "[Forme]") {
    // IL N'Y A PAS D'ERREUR DANS LE TEST, CELA DOIT MARCHER	
	Forme f2(Point(10,20), COULEURS::ROUGE);
	REQUIRE (f2.getPoint().getX() == 10);
	REQUIRE (f2.getPoint().getY() == 20);
	REQUIRE (f2.getCouleur() == COULEURS::ROUGE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);

	f2.getPoint().setX(15);
	f2.getPoint().setY(25);
	f2.setCouleur(COULEURS::JAUNE);
	REQUIRE (f2.getPoint().getX() == 15);
	REQUIRE (f2.getPoint().getY() == 25);
	REQUIRE (f2.getCouleur() == COULEURS::JAUNE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::ROUGE);
}



TEST_CASE("BoiteEnglobante", "[Forme]") {
	Forme f;
	REQUIRE (f.getLargeur() == 0);
	REQUIRE (f.getHauteur() == 0);
}

TEST_CASE("Cercle", "[Cercle]") {
   int compteur = Forme::prochainId();
   Cercle c1;
   Cercle c2(Point(10, 10), 10);

   REQUIRE(c1.toString() == "CERCLE 0 0 0");
   REQUIRE(c2.toString() == "CERCLE 0 0 10");

   c2.setRayon(5);
   REQUIRE(c2.getRayon()   == 5);
   REQUIRE(c2.toString()   == "CERCLE 10 10 5");
   REQUIRE(c2.getLargeur() == 10);
   REQUIRE(c2.getHauteur() == 10);

   REQUIRE(Forme::prochainId() == (compteur+2) );
}

TEST_CASE("Polymorphisme", "[Forme]") {
   Forme * f1 = new Cercle;
   Forme * f2 = new Rectangle;

   REQUIRE(f1->toString() == "CERCLE 0 0 0");
   REQUIRE(f2->toString() == "RECTANGLE 0 0 0 0");

   delete f1;
   delete f2;
}
*/

/*
TEST_CASE("Groupe", "[Forme]") {
   Groupe g;
   Cercle * f1 = new Cercle;
   Rectangle * f2 = new Rectangle;

	while(true)
	{
		std::string str;
		std::cin >> str;
		if (str.rfind("creer", 0) == 0)
		{
			std::cout << "creer" << std::endl;
			if (str.rfind("cercle", 7) == 0)
			{
				std::cout << "Creer cercle" << std::endl;
			}
		}
	}

   delete f1;
   delete f2;
}
*/

TEST_CASE("Clone de rectangle", "[Rectangle]")
{
	Rectangle r1;
	Rectangle * r2 = r1.clone();

	REQUIRE(r1.toString() == r2->toString());
	delete r2;
}

TEST_CASE("Clone de cercle", "[Cercle]")
{
	Cercle r1;
	Cercle * r2 = r1.clone();

	REQUIRE(r1.toString() == r2->toString());
	delete r2;
}


TEST_CASE("Clone de groupe", "[Groupe]")
{
	Groupe g1, * g2;
	Rectangle f1;
	Rectangle f2;

	g1.ajouterForme(f1);
	g1.ajouterForme(f2);

	g2 = g1.clone();

	g1.afficher();
	g2->afficher();

	std::cout << "CLONE" << std::endl;
	REQUIRE(g1.toString() == g2->toString());

	delete g2;
}
