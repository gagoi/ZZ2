#ifndef LIST_HPP_
#define LIST_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Cell.hpp"

template <typename T>
class List
{
private:
	Cell<T> * _first;
	Cell<T> * _last;
	std::size_t _size;
public:
	List();
	~List();
	bool isEmpty() const;
	std::size_t size() const;
	T front() const;
	T back() const;

	void push_back(T val);
	void push_front(T val);
	T pop_back();
	T pop_front();

	void display(std::ostream & os) const;

	template<typename T2>
	friend std::ostream & operator<<(std::ostream & out, List<T2> & t);
	template<typename T3>
	friend std::ostream & operator<<(std::ostream & out, Cell<T3> * t);

};

#include "List.tpp"

#endif
