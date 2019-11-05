#ifndef ITLIST_HPP_
#define ITLIST_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Cell.hpp"
#include "List.hpp"

template <typename T>
class ItList
{
	template <typename T8>
	friend class List;
private:
	Cell<T> * _c;
	ItList(Cell<T> * el);
public:
	ItList();


	void remove();

	T& operator*();
	const T& operator*() const;
	ItList<T>& operator++();
	ItList<T> operator++(int);
	ItList<T>& operator--();
	ItList<T> operator--(int);


	template <typename T2>
	friend bool operator!=(const ItList<T2> & i, const ItList<T2> & i2);
};


#include "ItList.tpp"

#endif
