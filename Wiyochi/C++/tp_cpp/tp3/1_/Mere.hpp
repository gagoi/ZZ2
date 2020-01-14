#ifndef _MERE_HPP_
#define _MERE_HPP_

#include <iostream>
#include <string>

class Mere
{
public:
    Mere();
    Mere(std::string n);
    ~Mere();
    std::string getNom();
    virtual void afficher();

    static int getNbMere();

    int att_public;

private:
    int att_priv;
    std::string nom;
    static int n_mere;

protected:
    int att_prot;
    
};

#endif // !_MERE_HPP_