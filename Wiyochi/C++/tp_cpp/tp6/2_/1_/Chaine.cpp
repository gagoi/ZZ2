#include "Chaine.hpp"
#include <cstring>

Chaine::OutOfRangeException::OutOfRangeException(const std::string& str) :
    std::out_of_range(str),
    _problem(str)
{
}

const char* Chaine::OutOfRangeException::what() const noexcept
{
    return _problem.c_str();
}

Chaine::null_pointer::null_pointer(const std::string& str) :
    std::logic_error(str)
{
}

Chaine::null_pointer::null_pointer() :
    std::logic_error("Null pointer")
{
}

Chaine::Chaine() :
    _capacite(0),
    _tab(nullptr)
{
}

Chaine::Chaine(int taille) :
    _capacite(taille > 0 ? taille+1 : 0),
    _tab(nullptr)
{
    if (_capacite)
    {
        try {
            _tab = new char[_capacite];
            _tab[0] = '\0';
        }
        catch (const std::bad_alloc& e)
        {
            _capacite = 0;
            throw;
        }
    }
}

Chaine::Chaine(const char* cstring) :
    _capacite(strlen(cstring) + 1),
    _tab(nullptr)
{
    try {
        _tab = new char[_capacite];
        strcpy(_tab, cstring);
        _tab[_capacite-1] = '\0';
    }
    catch (const std::bad_alloc& e)
    {
        _capacite = 0;
        throw;
    }
}

Chaine::Chaine(const Chaine& otherChaine) :
    _capacite(otherChaine._capacite),
    _tab(nullptr)
{
    if (_capacite)
    {
        try {
            _tab = new char[_capacite];
            strcpy(_tab, otherChaine._tab);
            _tab[_capacite-1] = '\0';
        }
        catch (const std::bad_alloc& e)
        {
            _capacite = 0;
            throw;
        }
    }
}

Chaine::~Chaine()
{
    delete[] _tab;
}

const char* Chaine::c_str() const
{
    return _tab;
}

int Chaine::getCapacite() const
{
    return _capacite - 1;
}

void Chaine::afficher(std::ostream& out) const
{
    out << _tab;
}

Chaine& Chaine::operator=(const Chaine& otherChaine)
{
    if (&otherChaine != this)
    {
        delete[] _tab;
        _tab = nullptr;

        _capacite = otherChaine._capacite;
        try {
            _tab = new char[_capacite];
            strcpy(_tab, otherChaine._tab);
            _tab[_capacite-1] = '\0';
        }
        catch (const std::bad_alloc& e)
        {
            _capacite = 0;
            throw;
        }
    }
    return *this;
}

char& Chaine::operator[](int index)
{
    if (_tab == nullptr)
        throw null_pointer();
    else if (index <= 0 || index > _capacite)
        throw OutOfRangeException("Index out of range");
    return _tab[index];
}

char Chaine::operator[](int index) const
{
    if (_tab == nullptr)
        throw null_pointer();
    else if (index <= 0 || index > _capacite)
        throw OutOfRangeException("Index out of range");
    return _tab[index];
}

std::ostream& operator<<(std::ostream& out, const Chaine& ch)
{
    out << ch.c_str();
    return out;
}

Chaine operator+(const Chaine& ch1, const Chaine& ch2)
{
    char buffer[ch1.getCapacite() + ch2.getCapacite() + 1];

    strcpy(buffer, ch1.c_str());
    strcat(buffer, ch2.c_str());

    Chaine c(buffer);
    return c;
}




void afficherParValeur(const Chaine ch)
{
    std::cout << "affichage par valeur:" << std::endl;
    ch.afficher();
}

void afficherParReference(const Chaine& ch)
{
    std::cout << "affichage par reference:" << std::endl;
    ch.afficher();
}