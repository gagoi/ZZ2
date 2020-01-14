#include "marvel.hpp"


//----------------------------------------
//----------------PERSONNE----------------
//----------------------------------------

const Personne Personne::INCONNU("Inconnu", "Inconnu", Personne::INDETERMINE);

Personne::Personne(std::string const & prenom, std::string const & nom, Genre genre) :
    _nom(nom),
    _prenom(prenom),
    _genre(genre)
{
}

Personne::Personne(Personne const & p) :
    _nom(p._nom),
    _prenom(p._prenom),
    _genre(p._genre)
{
}

Personne::~Personne()
{
}

std::string Personne::getNom() const
{
    return _nom;
}

std::string Personne::getPrenom() const
{
    return _prenom;
}

Personne::Genre Personne::getGenre() const
{
    return _genre;
}

void Personne::afficher(std::ostream& out) const
{
    std::string strGenre;
    switch (_genre)
    {
    case Genre::FEMME :
        strGenre = "[FEMME]";
        break;
    case Genre::HOMME :
        strGenre = "[HOMME]";
        break;
    case Genre::INDETERMINE :
        strGenre = "[INDETERMINE]";
        break;
    }
    out << _prenom << " " << _nom << " " << strGenre;
}

Personne& Personne::operator=(Personne const & p)
{
    if (&p != this)
    {
        _prenom = p._prenom;
        _nom = p._nom;
        _genre = p._genre;
    }
    return *this;
}

bool operator==(Personne const & p1, Personne const & p2)
{
    return (p1.getPrenom() == p2.getPrenom() && p1.getNom() == p2.getNom() && p1.getGenre() == p2.getGenre());
}

bool operator!=(Personne const & p1, Personne const & p2)
{
    return !(p1 == p2);
}

std::ostream& operator<<(std::ostream& out, Personne const & p)
{
    p.afficher(out);
    return out;
}



//----------------------------------------
//-----------------SUPER------------------
//----------------------------------------
Super::Super(std::string const & nom, Personne const & p) :
    _nom(nom),
    _personne(p),
    _anonymat(true)
{
}

Super::Super(Super const & o) :
    _nom(o._nom),
    _personne(o._personne),
    _anonymat(o._anonymat)
{
    std::for_each(o._capa.begin(), o._capa.end(), [this](Capacite* const & c)
    {
        _capa.push_back(c->clone());
    });
}

Super::~Super()
{
    std::for_each(_capa.begin(), _capa.end(), [this](Capacite* const & c)
    {
        delete c;
    });
}

std::string Super::getNom() const
{
    return _nom;
}

void Super::setNom(std::string const & n)
{
    _nom = n;
}

Personne Super::getIdentite() const
{
    if (_anonymat)
        throw AnonymeException();
    return _personne;
}

bool Super::estAnonyme() const
{
    return _anonymat;
}

void Super::setIdentite(Personne const & p)
{
    _personne = p;
    _anonymat = true;
}

void Super::enregistrer()
{
    _anonymat = false;
}

void Super::ajouter(Capacite * c)
{
    _capa.push_back(c);
}

int Super::getNiveau() const
{
    int total = 0;
    std::for_each(_capa.begin(), _capa.end(), [&](Capacite* const & c)
    {
        total += c->getNiveau();
    });
    return total;
}