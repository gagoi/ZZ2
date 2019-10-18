#include <iostream>

class Bavarde {
  std::string nom;
 public :
   Bavarde(std::string n):nom(n) {
      std::cout << "constructeur " << nom << std::endl;
   }
   ~Bavarde() {
      std::cout << "destructeur " << nom << std::endl;
   }
};

Bavarde g("global");

int main(int, char **) {
   Bavarde t("local");
   static Bavarde s("statlocal");

   //std::exit(1); // Sors de la fonction : donc local pas detruit.
   //std::terminate(); // Arrete tout : rien de libéré.
   //std::unexpected(); // ne s'appelle pas normalement : Pareil ?
   return 0;
}