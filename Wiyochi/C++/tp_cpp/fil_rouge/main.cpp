#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Forme.hpp"
#include "Groupe.hpp"
#include "Rectangle.hpp"
#include "Cercle.hpp"

bool treatCommand(const std::string& command, std::vector<Forme*>& list);
Forme* getFormeById(std::vector<Forme*>& list, int id);

int main()
{
    std::vector<Forme*> mainList;
    std::string command;

    do
    {
        std::cout << "$ ";
        std::getline(std::cin, command);
    } while (treatCommand(command, mainList));


    return 0;
}

bool treatCommand(const std::string& command, std::vector<Forme*>& list)
{
    std::istringstream iss(command);
    std::string nomCommand;
    bool continuer = true;
    int param1, param2, param3, param4;
    std::ostringstream retour;

    iss >> nomCommand;

    if (nomCommand == "creer")
    {
        std::string objet;
        iss >> objet;

        if (objet == "cercle")
        {
            if(iss >> param1 && iss >> param2 && iss >> param3)
            {
                if(iss >> param4)
                    list.push_back(new Cercle(param1, param2, param3, param4));
                else
                    list.push_back(new Cercle(param1, param2, param3));
                retour << " => " << list[list.size() - 1]->getId() << std::endl;
            }
            else
            {
                retour << "Parametres incorrects" << std::endl;
            }
        }
        else if (objet == "rectangle")
        {
            if(iss >> param1 && iss >> param2 && iss >> param3 && iss >> param4)
            {
                list.push_back(new Rectangle(param1, param2, param3, param4));
                retour << " => " << list[list.size() - 1]->getId() << std::endl;
            }
            else
            {
                retour << "Parametres incorrects" << std::endl;
            }
        }
        else if (objet == "groupe")
        {
            list.push_back(new Groupe());
            retour << " => " << list[list.size() - 1]->getId() << std::endl;
        }
        else
        {
            retour << "Pas d'objet a creer" << std::endl;
        }
    }
    else if (nomCommand == "afficher")
    {
        for (size_t i = 0; i < list.size(); i++)
        {
            if (list[i]->getDisplay())
                retour << list[i]->toString() << std::endl;
        }
    }
    else if (nomCommand == "ajouter")
    {
        if(iss >> param1 && iss >> param2)
        {
            if(param1 >= 0 && param1 < (int)list.size() && param2 >= 0 && param2 < (int)list.size())
            {
                Groupe* groupe = dynamic_cast<Groupe*>(getFormeById(list, param1));
                Forme* forme = getFormeById(list, param2);
                if (groupe && forme)
                {
                    groupe->ajouter(forme);
                    forme->setDisplay(false);
                    retour << " => " << forme->getId() << "->" << groupe->getId() << std::endl;
                }
                else
                {
                    retour << "Parametres incorrects" << std::endl;
                }
            }
            else
            {
                retour << "Parametres incorrects" << std::endl;
            }
        }
    }
    else if (nomCommand == "quitter")
    {
        retour << "bye" << std::endl;
        continuer = false;
    }
    else
    {
        retour << "Commande non valide" << std::endl;
    }

    std::cout << retour.str();

    return continuer;
}

Forme* getFormeById(std::vector<Forme*>& list, int id)
{
    Forme* f = nullptr;
    size_t i = 0;

    if(list.size() > 0)
    {
        i = 0;
        do {
            f = list[i];
            i++;
        } while (f->getId() != id);
    }
    return (f->getId() == id ? f : nullptr);
}