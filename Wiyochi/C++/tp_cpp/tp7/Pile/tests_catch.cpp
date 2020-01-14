#include "catch.hpp"
#include <cstring>
#include <sstream> // a mettre en commentaire
#include "Pile.hpp"

typedef Pile<int> PileInt;

TEST_CASE("Constructeur par defaut") {
   PileInt p; // cela implique que par defaut la capacite de la PileInt n'est pas nulle => pas d exception

   CHECK(  p.empty() );
   CHECK(  0 == p.size() );
}

TEST_CASE("Exceptions de mauvaise construction") {

   REQUIRE_THROWS_AS( PileInt(-1).empty(), std::invalid_argument& );
   REQUIRE_THROWS_AS( PileInt( 0).empty(), std::invalid_argument& );

}

TEST_CASE("Exception PileInt vide") {

   REQUIRE_THROWS_AS( PileInt().pop(), std::invalid_argument& );

}

TEST_CASE("Live PileInt") {
    PileInt p(10);

    CHECK(  p.empty() );
    CHECK(  0 == p.size() );

    p.push(5);

    CHECK( !p.empty() );
    CHECK( 1 == p.size() );
    CHECK( 5 == p.top() );

    p.push(2);
    p.push(1);

    CHECK( 3 == p.size() );
    CHECK( 1 == p.top() );

    p.pop();

    CHECK( 2 == p.size() );
    CHECK( 2 == p.top() );

    p.pop();
    p.pop();

    CHECK( 0 == p.size() );

}