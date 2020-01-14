#ifndef FORME_HPP_
#define FORME_HPP_

#include <string>
#include "Point.hpp"

enum class COULEURS
{
	NOIR,
	BLANC,
	BLEU,
	ROUGE,
	JAUNE,
	VERT
};

class Forme
{
public:
	Forme();
	Forme(int x, int y, int w, int h);
	Forme(Point p, COULEURS c);
	virtual ~Forme();

	Point& getPoint();
	void setX(int x);
	void setY(int y);
	void setLargeur(int w);
	void setHauteur(int h);
	int getLargeur() const;
	int getHauteur() const;
	COULEURS getCouleur() const;
	void setCouleur(COULEURS c);
	int getId() const;
	void setDisplay(bool d);
	bool getDisplay() const;

	virtual std::string toString() const = 0;
	virtual Forme * clone() const = 0;

	static int prochainId();

protected:
	Point _origin;
	int _width;
	int _height;
	COULEURS _couleur;
	int _id;
	bool _display;

	static int nbFormes;
};

#endif
