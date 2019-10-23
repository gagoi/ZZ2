#ifndef CELL_HPP_
#define CELL_HPP_

#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Cell
{
private:
	T _value;
	Cell<T> * _next;
	Cell<T> * _prev;
public:	
	Cell(T value, Cell * prev, Cell * next);
	Cell<T> * next() const;
	Cell<T> * prev() const;
	void setNext(Cell<T> * next);
	void setPrev(Cell<T> * prev);
	T getValue() const;

	template<typename T2>
	friend std::ostream operator<<(std::ostream & out, Cell<T2> & cell);
};

#include "Cell.tpp"

#endif
