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
	T operator*();
};

template <typename T>
bool operator!=(const ItList<T> & i, const ItList<T> & i2);

#include "ItList.tpp"

#endif
