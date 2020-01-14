#ifndef marvel__hpp
#define marvel__hpp

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>

//----------------------------------------
//----------------PERSONNE----------------
//----------------------------------------
class Personne
{
public:
    enum Genre
    {
        HOMME,
        FEMME,
        INDETERMINE
    };

    Personne(std::string const & prenom, std::string const & nom, Genre genre = INDETERMINE);
    Personne(Personne const & p);
    ~Personne();

    std::string getNom() const;
    std::string getPrenom() const;
    Genre getGenre() const;
    void afficher(std::ostream& out = std::cout) const;
    Personne& operator=(Personne const & p);

    static const Personne INCONNU;
    
private:
    std::string _nom;
    std::string _prenom;
    Genre       _genre;
};

bool operator==(Personne const & p1, Personne const & p2);
bool operator!=(Personne const & p1, Personne const & p2);
std::ostream& operator<<(std::ostream& out, Personne const & p);




//----------------------------------------
//-----------------CAPACITE---------------
//----------------------------------------
class Capacite
{
public:
    Capacite(std::string const & n, int l) : _nom(n), _niveau(l) {}
    virtual ~Capacite() {}
    virtual Capacite* clone() const = 0;
    
    virtual void utiliser(std::ostream & out = std::cout) = 0;
    int getNiveau() const { return _niveau; }
    std::string getNom() const { return _nom; }

protected:
    std::string _nom;
    int _niveau;
};


// Physique
class Physique : public Capacite
{
public:
    Physique(std::string const & n, int l) : Capacite(n, l) {}
    ~Physique() {}
    Physique* clone() const { return new Physique(_nom, _niveau); }

    void exercer(std::ostream & out = std::cout) { out << _nom << " [" << _niveau << "]"; }
    void utiliser(std::ostream & out = std::cout) { exercer(out); }
};


// Materiel
class Materiel : public Capacite
{
public:
    Materiel(std::string const & n, int l) : Capacite(n, l) {}
    ~Materiel() {}
    Materiel* clone() const { return new Materiel(_nom, _niveau); }

    void actionner(std::ostream & out = std::cout) { out << _nom << " [" << _niveau << "] en action"; }
    void utiliser(std::ostream & out = std::cout) { actionner(out); }
};


// Psychique
class Psychique : public Capacite
{
public:
    Psychique(std::string const & n, int l) : Capacite(n, l) {}
    ~Psychique() {}
    Psychique* clone() const { return new Psychique(_nom, _niveau); }

    void penser(std::ostream & out = std::cout) { out << _nom << " [" << _niveau << "]"; }
    void utiliser(std::ostream & out = std::cout) { penser(out); }
};




//----------------------------------------
//-----------------SUPER------------------
//----------------------------------------
class Super
{
public:
    Super(std::string const & nom, Personne const & p);
    Super(Super const & o);
    ~Super();

    std::string getNom() const;
    void setNom(std::string const & n);
    bool estAnonyme() const;
    Personne getIdentite() const;
    void setIdentite(Personne const & p);
    void enregistrer();
    void ajouter(Capacite * c);
    int getNiveau() const;

private:
    std::string _nom;
    Personne _personne;
    bool _anonymat;
    std::vector<Capacite*> _capa;
};


class AnonymeException : std::exception
{
public:
    AnonymeException() : std::exception(), error("identite anonyme") {}
    ~AnonymeException() {}
    AnonymeException& operator=(AnonymeException const & o) { error = o.what(); return *this; }
    const char* what() const noexcept { return error.c_str(); }

private:
    std::string error;
};




//----------------------------------------
//-----------------EQUIPE-----------------
//----------------------------------------
class Equipe
{
public:
    Equipe(std::string const & n) : _nom(n) {}
    ~Equipe() {
        std::for_each(_equipe.begin(), _equipe.end(), [&](Super* const & s)
        {
            delete s;
        });
    }

    int getNombre() const { return _equipe.size(); }
    void ajouter(Super* super) { _equipe.push_back(super); }
    int getNiveau() const {
        int niveau = 0;
        std::for_each(_equipe.begin(), _equipe.end(), [&](Super* const & s)
        {
            niveau += s->getNiveau();
        });
        return niveau;
    }
    
private:
    std::string _nom;
    std::vector<Super*> _equipe;
};

#endif
