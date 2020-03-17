#include <iostream>
#include <cstdlib>

class Bavarde {
	private:
		int _i;
	public:
	Bavarde(int i=0):_i(i)
	{
		std::cout << "Construction de " << _i << std::endl;
	}
	~Bavarde()
	{
		std::cout << "Tais-toi " << _i << std::endl;
	}
	int getI()
	{
		return _i;
	}

	void afficher()
	{
		std::cout << "Affichage de " << getI() << std::endl;
	}

} bizarre(1);

class Couple {
	private :
	Bavarde _b1,_b2;
	public:
	Couple(Bavarde b1, Bavarde b2):_b1(b1), _b2(b2)
	{

	}
	~Couple()
	{
	}
};


Bavarde globale(2);

void fonction(Bavarde b) {
  std::cout << "code de la fonction" << b.getI() << std::endl;
}

/*
int main(int, char **) {
  Bavarde b;
  Bavarde * p = new Bavarde(3);
  fonction(b);

	std::cout << Bavarde(0).getI() << std::endl;

	delete p;
  return 0;
}
*/
/*
int main(int, char **) {
  const int TAILLE = 20;
  Bavarde   tab1[TAILLE];
  Bavarde * tab2 = new Bavarde[TAILLE];

  for (int i =0; i < TAILLE; ++i)
  {
	std::cout << i << std::endl;
     tab1[i].afficher();
     tab2[i].afficher();
  }

  delete[] tab2;
  return 0;
}*/

class Famille{
	private:
		Bavarde * tab;
	public:
		Famille(int taille)
		{
			tab = new Bavarde[taille];
		}
		~Famille()
		{
			delete[] tab;
		}
};


int main(int, char**){
	//Bavarde b1(12);
	//Bavarde b2(59);

	//Couple c1(b1, b2);

//	Famille f1(12);

//	Famille f2(12);

	Bavarde * b1 = (Bavarde*) malloc(sizeof(Bavarde));
	std::cout << b1->getI() << std::endl;
	free(b1);
	return 0;
}