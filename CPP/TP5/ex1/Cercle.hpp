#ifndef _CERCLE_H_
#define _CERCLE_H_

#include <string>

#include "Forme.hpp"

class Cercle : public Forme
{
	private:
		int _r;
	public:
		Cercle(const Point&, int w, int h);
		Cercle(int x, int y, int w, int h);
		Cercle(const Point& p, int r);
		Cercle(int x = 0, int y = 0, int r = 0);
		virtual std::string toString() const;
		void setRayon(int r);
		int getRayon() const;

};

#endif