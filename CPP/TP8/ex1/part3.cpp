#include <iostream>
#include <string>
#include <vector>
#include <queue>

class ZZ {
  std::string _nom, _prenom;
  double _note;

  friend bool operator<(const ZZ & zz1 , const ZZ & zz2);
  friend std::ostream& operator<<(std::ostream& stream, const ZZ & zz1);

public:
  ZZ(std::string nom, std::string prenom, double note):
	_nom(nom), _prenom(prenom), _note(note)
  {

  }
};

bool operator<(const ZZ & zz1 , const ZZ & zz2)
{
	return zz1._note < zz2._note;
}

std::ostream& operator<<(std::ostream& stream, const ZZ & zz1)
{
	stream << zz1._nom << " " << zz1._prenom << " : " << zz1._note;
	return stream;
}



typedef std::vector<ZZ>  vzz;

int main(int, char**)
{
	ZZ zz("ZANGLA", "Jérémy", 12);
	ZZ zz2("Kiki", "Mathieu", 11.5);
	std::cout << (zz < zz2 ? zz2 : zz) << std::endl;

	vzz zzs;
	zzs.push_back(zz);
	zzs.push_back(zz2);

	std::priority_queue<ZZ> queue;

	for (auto zz : zzs)
		queue.push(zz);


	while (!queue.empty())
	{
		std::cout << queue.top() << std::endl;
		queue.pop();
	}



	std::vector<ZZ*> pzz;
	ZZ* z1 = new ZZ("feef1", "adz", 10);
	ZZ* z2 = new ZZ("feef2", "adz", 10);
	ZZ* z3 = new ZZ("feef3", "adz", 10);

	pzz.push_back(z1);
	pzz.push_back(z2);
	pzz.push_back(z3);

	for (auto z : pzz)
		delete z;
	
	return 0;
}