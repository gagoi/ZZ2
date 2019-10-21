#ifndef _FORME_H_
#define _FORME_H_

#include <string>
#include <sstream>

#include "Point.hpp"

enum class COULEURS
{
	NOIR, BLANC, ROUGE, VERT, BLEU, MARRON, JAUNE, ORANGE, VIOLET, ROSE, POURPRE, CYAN, MAGENTA, LILA, TAUPE, FF00FF, TRANSPARENT, GRIS, GRIS_CLAIR, KAKI, ZINZOLIN
};

class Forme
{
	protected:
		Point _p;
		int _w;
		int _h;
		COULEURS _couleur;
		static int nbFormes;
		int _id;
	public:
		Forme();
		Forme(Point, COULEURS);
		Forme(const Point& p, int w, int h);
		Forme(const Forme& f);
		void setCouleur(COULEURS coleur);
		virtual ~Forme();
		Point getPoint() const;
		COULEURS getCouleur() const;
		int getId() const;
		virtual std::string toString() const;
		static int prochainId();
		void setX(int x);
		void setY(int y);
		int getHauteur() const;
		int getLargeur() const;
		virtual Forme* clone() const;

};

#endif