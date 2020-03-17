#include "catch.hpp"
#include <cstring>
#include <sstream> // a mettre en commentaire 
#include "Conteneur.hpp"

TEST_CASE("Constructeur par defaut") {
    Conteneur c;
    CHECK(0 == c.size());
    CHECK(10 == c.capacity());
}

TEST_CASE("Constructeur taille changée") {
    Conteneur c(5);
    CHECK(0 == c.size());
    CHECK(5 == c.capacity());
}

TEST_CASE("Constructeur par copie") {
    Conteneur c(5);

    c.push_back(12);
    c.push_back(4.2);

    Conteneur c2(c);

    CHECK(c.size() == c2.size());
    CHECK(c.capacity() == c2.capacity());
    CHECK(c[0] == c2[0]);
    CHECK(c[1] == c2[1]);
}

TEST_CASE("Ajout d'un élément") {
    Conteneur c;
    c.push_back(12.1);

    CHECK(1 == c.size());
}

TEST_CASE("Ajout d'un élément avec reallocation") {
    Conteneur c(1);
    c.push_back(12.1);
    c.push_back(13);

    CHECK(2 == c.size());
    CHECK(2 == c.capacity());
}

TEST_CASE("Indexation lecture") {
    Conteneur c;
    c.push_back(12.1);

    CHECK(12.1 == c[0]);
}

TEST_CASE("Indexation écriture") {
    Conteneur c;
    c.push_back(12.1);
    CHECK(12.1 == c[0]);

    c[0] = 8.33;
    CHECK(8.33 == c[0]);
}

TEST_CASE("Opérateur de flux") {
    Conteneur c;
    c.push_back(12.1);
    c.push_back(7);
    c.push_back(4.2);
    std::stringstream ss;
    ss << c;

    CHECK(0 == strcmp(ss.str().c_str(), "[12.1,7,4.2]"));
}

TEST_CASE("Opérateur de concaténation") {
    Conteneur c1, c2, c3;
    c1.push_back(8.5);
    c2.push_back(1.98);


    CHECK((c1 + c2).size() == c1.size() + c2.size());
    CHECK((c1 + c2)[0] == c1[0]);
    CHECK((c1 + c2)[1] == c2[0]);
}

TEST_CASE("Opérateur d'affectation") {
    Conteneur c1, c2;
    c1.push_back(11);

    c2 = c1;

    CHECK(c2.size() == c1.size());
    CHECK(c2.capacity() == c1.capacity());
    CHECK(c1[0] == c2[0]);
}