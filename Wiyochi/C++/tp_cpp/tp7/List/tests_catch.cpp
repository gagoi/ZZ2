#include "catch.hpp"
#include <cstring>
#include <sstream> // a mettre en commentaire
#include "List.hpp"

typedef List<int> ListInt;

TEST_CASE("Liste Vide")
{
   ListInt l;

   REQUIRE( l.empty() == true );
   REQUIRE( l.size() == 0 );
}

TEST_CASE("Constructeur par copie")
{
   ListInt l1;
   std::ostringstream oss;
   
   l1.push_back(12);
   l1.push_back(89);
   l1.push_back(56);

   ListInt l2(l1);
   l2.front() = 1;

   oss << l2;

   REQUIRE( oss.str() == "[ 1, 89, 56 ]" );
}

TEST_CASE("push_back")
{
   ListInt l;
   int a = 56;

   l.push_back(10);
   l.push_back(45);
   l.push_back(a);

   REQUIRE( l.empty() == false );
   REQUIRE( l.size() == 3 );
   REQUIRE( l.front() == 10 );
   REQUIRE( l.back() == a );
}

TEST_CASE("Affichage")
{
   ListInt l;
   std::ostringstream oss;
   int a = 56;

   l.push_back(10);
   l.push_back(45);
   l.push_back(a);

   oss << l;

   REQUIRE( oss.str() == "[ 10, 45, 56 ]" );
}

TEST_CASE("push_front")
{
   ListInt l;
   std::ostringstream oss;
   int a = 56;

   l.push_front(10);
   l.push_front(45);
   l.push_front(a);

   oss << l;

   REQUIRE( oss.str() == "[ 56, 45, 10 ]" );
}

TEST_CASE("front non const")
{
   ListInt l;
   std::ostringstream oss;
   
   l.push_front(45);
   l.push_back(8);
   l.push_front(78);

   l.front() = 456;

   oss << l;

   REQUIRE( oss.str() == "[ 456, 45, 8 ]" );
}

TEST_CASE("pop_front")
{
   ListInt l;
   std::ostringstream oss;

   for (int i = 0; i < 5; i++)
      l.push_front(i);

   REQUIRE( l.pop_front() == 4 );

   oss << l;

   REQUIRE( oss.str() == "[ 3, 2, 1, 0 ]");
}

TEST_CASE("pop_back")
{
   ListInt l;
   std::ostringstream oss;

   for (int i = 0; i < 5; i++)
      l.push_front(i);

   REQUIRE( l.pop_back() == 0 );

   oss << l;

   REQUIRE( oss.str() == "[ 4, 3, 2, 1 ]");
}


// Iterators

TEST_CASE("iterator default constructor")
{
   ListInt list;
   for (size_t i = 0; i < 10; i++)
      list.push_back(1);

   for (ListInt::iterator it = list.begin(); it != list.end(); it++)
   {
      REQUIRE( *it == 1 );
   }   
}

TEST_CASE("find")
{
   ListInt list;
   for (size_t i = 0; i < 10; i++)
      list.push_back(i);

   ListInt::iterator it = list.find(5);
   REQUIRE( *it == 5 );
}

TEST_CASE("remove")
{
   std::ostringstream oss;
   ListInt list;
   for (size_t i = 0; i < 5; i++)
      list.push_back(i);

   ListInt::iterator it = list.find(2);
   list.remove(it);

   oss << list;
   REQUIRE( oss.str() == "[ 0, 1, 3, 4 ]");
}

TEST_CASE("insert")
{
   std::ostringstream oss;
   ListInt list;
   for (size_t i = 0; i < 5; i++)
      list.push_back(i);

   ListInt::iterator it = list.find(2);
   list.insert(it, 10);

   oss << list;
   REQUIRE( oss.str() == "[ 0, 1, 2, 10, 3, 4 ]");
}