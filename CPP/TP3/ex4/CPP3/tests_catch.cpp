#include <fstream>
#include <iostream>

#include "producteurAleatoire.hpp"
#include "producteur.hpp"
#include "producteurPremiersEntiers.hpp"
#include "statisticien.hpp"
#include "catch.hpp"

TEST_CASE("Producteur_Initialisation") {
  ProducteurPremiersEntiers p;
  REQUIRE( p.getTravail() == 0);
}

TEST_CASE("Producteur_travail2") {
  ProducteurPremiersEntiers p;
  p.produire(10,"test01.txt");
  p.produire(10, "test01.txt");
  p.produire(10, "test01.txt");
  REQUIRE ( p.getTravail() == 3);
}

TEST_CASE("Producteur_Travail3") {

    const int         DEMANDE    = 10;
    const std::string NOM_FICHIER("test01.txt");
    int               lecture, i;
    ProducteurPremiersEntiers        p; 


    p.produire(DEMANDE, NOM_FICHIER.c_str());

    std::ifstream fichier(NOM_FICHIER.c_str());

    REQUIRE(fichier.is_open());

    if (!fichier.eof()) {
      fichier >> lecture; 
      REQUIRE(DEMANDE == lecture);
      for (i = 0; i < DEMANDE; ++i) {
        fichier >> lecture;
        REQUIRE( lecture == (i+1) );
      }
    
    REQUIRE(i == DEMANDE);
    CHECK(fichier.eof());
    fichier.close();

    REQUIRE(p.getTravail() == 1);
  }
}

TEST_CASE("Statisticien_Initialisation") {
  Statisticien p;
  REQUIRE_FALSE(p.aCalcule());
}

TEST_CASE("Statisticien_Moyenne") {
  const std::string NOM_FICHIER("test01.txt");
  const int SOMME_10 = 55;

  Statisticien p;
  p.acquerir(NOM_FICHIER);
  REQUIRE(p.somme() == SOMME_10);
}

TEST_CASE("Producteur_Aleatoire") {
  const int         DEMANDE    = 10;
  const std::string NOM_FICHIER("test02.txt");

  srand((unsigned int) time(0));
  ProducteurAleatoire p;
  p.produire(DEMANDE, NOM_FICHIER);

 
}
