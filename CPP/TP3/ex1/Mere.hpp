#ifndef MERE_H_
#define MERE_H_

#include <string>
#include <iostream>


class Mere
{
	protected:
		int _id;
		std::string _nom;
		static int cpt;
	public:
		Mere(int id = 0, std::string = "");
		~Mere();
		int getCpt();
		std::string getNom();
		virtual void afficher();
};

#endif