#include "catch.hpp"
#include <sstream>
#include "Vector.hpp"

TEST_CASE("Constructeur par défaut") {
    Vector v;
    CHECK( v.getCapacity() == 10 );
    CHECK( v.getSize() == 0 );
}

TEST_CASE("Constructeur avec capacité") {
    Vector v(12);
    CHECK( v.getCapacity() == 12 );
    CHECK( v.getSize() == 0 );
}

TEST_CASE("Constructeur par copie") {
    
}

TEST_CASE("push_back") {
    Vector v(5);
    
    for(int i = 0; i < 5; i++)
        v.push_back((double)i);

    CHECK( v.getCapacity() == 5 );
    CHECK( v.getSize() == 5 );
    for(int i = 0; i < 5; i++)
        CHECK( v.at(i) == i );

    v.push_back(0.002);

    CHECK( v.getCapacity() == 10 );
    CHECK( v.getSize() == 6 );
}

TEST_CASE("operateur =") {
    Vector v1(5);
    Vector v2(10);
    
    for (int i = 0; i < 5; i++)
        v1.push_back(i);
    for (int i = 0; i < 10; i++)
        v1.push_back(0);

    v2 = v1;

    CHECK( v2.getCapacity() == v1.getCapacity() );
    for (int i = 0; i < 5; i++)
        CHECK( v2[i] == v1[i] );
}

TEST_CASE("operateur []") {
    Vector v(5);
    std::stringstream ss;
    
    for(int i = 0; i < 5; i++)
        v.push_back(0.0);
    for(int i = 0; i < 5; i++)
        v[i] = i;

    for(int i = 0; i < 5; i++)
    {
        CHECK( v[i] == i );
        ss << v[i];
    }

    CHECK( ss.str() == "01234" );
}

TEST_CASE("operateur <<") {
    Vector v(5);
    std::stringstream ss;
    
    for(int i = 0; i < 5; i++)
        v.push_back(i);

    ss << v;

    CHECK( ss.str() == "[0,1,2,3,4]" );
}

TEST_CASE("operateur +") {
    Vector v1(5);
    Vector v2(5);

    for (int i = 0; i < 5; i++)
        v2.push_back(i);
    v1.push_back(12);
    v1.push_back(12);
    
    Vector v3;

    v3 = v1 + v2;

    CHECK( v3.getCapacity() == 10);

    CHECK( v3[0] == v1[0] );
    CHECK( v3[1] == v1[1] );
    for (int i = 2; i < v3.getSize(); i++)
        CHECK( v3[i] == v2[i-2] );
}