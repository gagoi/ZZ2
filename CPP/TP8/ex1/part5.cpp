#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <utility>
#include <fstream>

// OU en C++ 2011
// using mss = std::map<string, string> ;

const std::string& first(const std::pair<std::string,std::string>& p) { return p.first; }
std::string paire(const std::pair<std::string,std::string>& p) { return p.first + " " + p.second;};

template<typename M>
struct MapInserterIterator {
	struct MapInserter {
		M &m;

		template<typename P>
		void operator=(P const&p) {
			m.insert(p);
		}
	};

	M &m;

	void operator++() {}
	MapInserter operator*() { return {m}; }
};

template<typename M>
MapInserterIterator<M> mapInserterIterator(M &m) {
	return {m};
}

int main(int argc, char** argv) {
	std::map<std::string, std::string> liste; 
	std::map<std::string, std::string> liste2;

	liste.insert(std::pair<std::string, std::string>("k1", "v1"));
	liste.insert(std::pair<std::string, std::string>("k2", "v2"));
	liste.insert(std::pair<std::string, std::string>("k3", "v3"));
	liste.insert(std::pair<std::string, std::string>("k4", "v4"));

	std::copy(std::begin(liste), std::end(liste), mapInserterIterator(liste2));

	

	//std::copy(liste.begin(), liste.end(), std::back_inserter(liste2));

	std::map<std::string, std::string>::const_iterator it = liste.begin();
	while(it!=liste.end()) {
		std::cout << it->first  << " "
			<< it->second << std::endl;
		++it;
	}

	std::transform(liste.begin(), liste.end(), std::ostream_iterator<std::string>(std::cout, " "), first);
	std::transform(liste.begin(), liste.end(), std::ostream_iterator<std::string>(std::cout, " "), paire);

	for(auto&& p: liste)
		std::cout << paire(p) << " ";


	std::cout << std::endl << "------------------------------------" << std::endl;

	std::fstream file(argc != 2 ? "test.txt" : argv[1]);
	if(file.is_open())
	{
		std::string str, str2;

		while (file >> str && file >> str2)
			liste2.insert(std::pair<std::string, std::string>(str, str2));

		std::cout << std::endl;
		for (auto e : liste2)
			std::cout << paire(e) << std::endl;
	} else
		std::cout << "non trouvé" << std::endl;

	std::string str;
	while (std::cin >> str)	
	{
		std::cout << liste2[str] << std::endl;
	}

	return 0;
}