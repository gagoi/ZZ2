#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

typedef std::map<std::string, std::string> mss;
// OU en C++ 2011
// using mss = std::map<string, string> ;

const std::string& first(const std::pair<std::string,std::string>& p) { return p.first; }

int main(int, char**) {
	std::map<std::string, std::string> liste;

	liste.insert("k1", "v1");
	liste.insert("k2", "v2");
	liste.insert("k3", "v3");
	liste.insert("k4", "v4");

	std::map<std::string, std::string>::const_iterator it = liste.begin();
	while(it!=liste.end()) {
		std::cout << it->first  << " "
			<< it->second << std::endl;
		++it;
	}

	transform(liste.begin(), liste.end(),
	std::ostream_iterator<std::string>(std::cout, " "), first);

	return 0;
}