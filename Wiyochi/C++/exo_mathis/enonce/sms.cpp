#include "sms.hpp"

Telephone::Telephone() : _num("")
{

}

Telephone::Telephone(std::string numero) : _num(numero)
{

}

Telephone::~Telephone()
{

}

std::string Telephone::getNumero() const
{
    return _num;
}

void Telephone::setNumero(std::string numero)
{
    _num = numero;
}

Reseau::Reseau()
{

}

Reseau::~Reseau()
{

}

void Reseau::ajouter(std::string num)
{
    Telephone * tel = new Telephone(num);
    ListTel.insert(tel);
}

std::string Reseau::lister() const
{
    std::string resultat;
    std::set<Telephone*>::iterator it;
    for(it=ListTel.begin(); it!=ListTel.end(); it++)
    {
        resultat += (*it)->getNumero();
        resultat += "\n";
    }

    return resultat;
}


Telephone* Reseau::trouverTel(std::string num) const
{
    std::set<Telephone*, comparTel>::iterator it;
    it = ListTel.begin();
    while((*it)->getNumero() != num)
    {
        it++;
    }
    return *it;

}

Reseau* Telephone::getReseau()
{

}