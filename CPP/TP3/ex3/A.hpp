#ifndef A_H
#define A_H

#include "B.hpp"

class A
{
	private:
		int i;
	public:
		A(int k = 0);
		void send(B * b);
		void exec(int k);
};

#endif