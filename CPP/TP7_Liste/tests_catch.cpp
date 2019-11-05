#include "catch.hpp"
#include <cstring>
#include "List.hpp"
#include <sstream>

typedef List<int> List_int;

TEST_CASE("push_back", "[List]") {
   List_int l;
   std::ostringstream oss;
   REQUIRE(l.isEmpty());
   l.push_back(12);
   l.push_back(12);
   l.push_back(4);
   l.push_back(19728425);
   oss << l;
   REQUIRE(oss.str() == "12 12 4 19728425 ");
}

TEST_CASE("push_front", "[List]") {
   List_int l;
   std::ostringstream oss;
   REQUIRE(l.isEmpty());
   l.push_front(19728425);
   l.push_front(4);
   l.push_front(12);
   l.push_front(12);
   oss << l;
   REQUIRE(oss.str() == "12 12 4 19728425 ");
}

TEST_CASE("front & back", "[List]") {
   List_int l;

   l.push_back(450);
   l.push_back(32);
   l.push_back(20);

   REQUIRE(l.front() == 450);
   REQUIRE(l.back() == 20); 

   l.push_front(42);
   l.push_front(732);
   l.push_front(210);

   REQUIRE(l.front() == 210);
   REQUIRE(l.back() == 20); 
}

TEST_CASE("Exceptions", "[List]") {
   List_int l;
   REQUIRE_THROWS_AS(l.front(), std::out_of_range);
   REQUIRE_THROWS_AS(l.back(), std::out_of_range);
   REQUIRE_THROWS_AS(l.pop_front(), std::out_of_range);
   REQUIRE_THROWS_AS(l.pop_back(), std::out_of_range);
}

TEST_CASE("Size", "[List]") {
   List_int l;

   REQUIRE(l.size() == 0);
   l.push_back(15);
   REQUIRE(l.size() == 1);
   l.push_front(16);
   REQUIRE(l.size() == 2);
   l.pop_back();
   REQUIRE(l.size() == 1);
   l.pop_front();
   REQUIRE(l.size() == 0);
}

TEST_CASE("Pops", "[List]") {
   List_int l;

   l.push_back(12);
   l.push_front(30);
   l.push_back(152);

   REQUIRE(l.pop_front() == 30);
   REQUIRE(l.pop_back() == 152);
   REQUIRE(l.size() == 1);
}

TEST_CASE("Constructeur par copie", "[List]"){
   List_int l1;

   std::ostringstream oss1, oss2;

   l1.push_back(12);
   l1.push_back(1586526);
   l1.push_back(1);

   List_int l2 = l1;

   oss1 << l1;
   oss2 << l2;

   REQUIRE(oss1.str() == oss2.str());
}

TEST_CASE("Operator=", "[List]"){
   List_int l1;
   List_int l2;

   std::ostringstream oss1, oss2;

   l1.push_back(12);
   l1.push_back(1586526);
   l1.push_back(1);

   l2 = l1;

   oss1 << l1;
   oss2 << l2;

   REQUIRE(oss1.str() == oss2.str());
}

TEST_CASE("Parcourt it", "[ItList]") {
   List_int l1;
   l1.push_back(1);  
   l1.push_back(2);
   auto i = l1.begin();
   REQUIRE(*i++ == 1);
   REQUIRE(*i == 2);
}

TEST_CASE("Modification via it", "[ItList]") {
   List_int l1;
   l1.push_back(1);
   auto i = l1.begin();
   REQUIRE(*i == 1);
   *i = 3;
   REQUIRE(*i == 3);
}

TEST_CASE("Find", "[ItList]") {
   List_int l1;
   l1.push_back(1);
   l1.push_back(2);
   l1.push_back(3);
   l1.push_back(4);
   l1.push_back(5);

   auto i = l1.find(2);
   REQUIRE(*i == 2);
   i = l1.find(5);
   REQUIRE(*i == 5);
   /*
   i = l1.find(-1);
   REQUIRE_THROWS_AS(*i, std::exception);
   */
}

TEST_CASE("Remove", "[ItList]")
{

}