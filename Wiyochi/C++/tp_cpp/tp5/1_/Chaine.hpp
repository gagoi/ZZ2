#ifndef CPP5__CHAINE_HPP
#define CPP5__CHAINE_HPP

#include <iostream>
#include <fstream>

class Chaine 
{
public:
    Chaine();
    Chaine(int taille);
    Chaine(const char* cstring);
    Chaine(const Chaine& otherChaine);
    ~Chaine();

    const char* c_str() const;
    int getCapacite() const;
    void afficher(std::ostream& out = std::cout) const;

    Chaine& operator=(const Chaine& otherChaine);
    char& operator[](int index);
    char operator[](int index) const;

private:
    int _capacite;
    char* _tab;
};

std::ostream& operator<<(std::ostream& out, const Chaine& ch);
Chaine operator+(const Chaine& ch1, const Chaine& ch2);

void afficherParValeur(const Chaine ch);
void afficherParReference(const Chaine& ch);

#endif
