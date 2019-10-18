#ifndef PILE_HPP_
#define PILE_HPP_

#include <iostream>
#include <string>
#include <vector>

class Pile
{
private:
	int _capa; // Max element.
	int * _tab;
	int _size; // Nb élément
public:
	Pile(int capa = 1);
	~Pile();
	bool empty() const;
	void push(const int i);
	int pop();
	int top() const;
	int size() const;
};

#endif
