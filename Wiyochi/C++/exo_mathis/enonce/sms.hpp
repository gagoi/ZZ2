#ifndef __SMS
#define __SMS
#include <string>
#include <set>
#include <iostream>

class Reseau;
class Telephone;

class Telephone
{
    private:
        std::string _num;
    public:
        Telephone();
        Telephone(std::string);
        ~Telephone();
        std::string getNumero() const;
        void setNumero(std::string);
        Reseau* getReseau() const;

};

class comparTel
{
    public:
        bool operator()(const Telephone* T1, const Telephone* T2)
        {
            return T1->getNumero() < T2->getNumero();
        }

};

class Reseau
{
    private:
        std::set<Telephone*, comparTel> ListTel;
    public:
        Reseau();
        ~Reseau();
        void ajouter(std::string);
        std::string lister() const;
        Telephone* trouverTel(std::string) const;
        
};

#endif