#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

const std::string& first(const std::pair<std::string,std::string>& p) { return p.first; }
const std::string pair(const std::pair<std::string,std::string>& p) { return p.first + " " + p.second; }

int main(int, char**) {
 std::map<std::string, std::string> liste;
 std::map<std::string, std::string> liste2;

 liste.insert(std::make_pair("1", "un"));
 liste.insert(std::make_pair("2", "deux"));
 liste.insert(std::make_pair("3", "trois"));
 liste.insert(std::make_pair("4", "quatre"));
 liste.insert(std::make_pair("5", "cinq"));

 std::for_each(liste.begin(), liste.end(),
    [](std::pair<std::string,std::string> const & p)
    {
        std::cout << p.first << " " << p.second << std::endl;
    });

 std::transform(liste.begin(), liste.end(), 
   std::ostream_iterator<std::string>(std::cout, " "), pair);

 std::transform(liste.begin(), liste.end(), 
   std::ostream_iterator<std::string>(std::cout, " "), first);
  
 return 0;
}