#include "List.hpp"

// Constructeur de cell
template<typename T>
List<T>::Cell::Cell(T v, Cell* prev, Cell* next) :
    _value(v),
    _previous(prev),
    _next(next)
{
}

// List
template<typename T>
List<T>::List() :
    _first(nullptr),
    _last(nullptr)
{
}

template<typename T>
List<T>::List(List<T> const & o) :
    _first(nullptr),
    _last(nullptr)
{
    for (Cell* curr = o._first; curr != nullptr; curr = curr->_next)
        push_back(curr->_value);
}

template<typename T>
List<T>::~List()
{
    Cell* tmp = nullptr;
    Cell* curr = _first;
    while (curr != nullptr)
    {
        tmp = curr;
        curr = curr->_next;
        delete tmp;
    }
}

template<typename T>
bool List<T>::empty() const
{
    return _first == nullptr;
}

template<typename T>
void List<T>::push_back(T v)
{
    Cell* elem = new Cell(v, _last, nullptr);
    if (!_first)
        _first = elem;
    else
        _last->_next = elem;
    _last = elem;
}

template<typename T>
void List<T>::push_front(T v)
{
    Cell* elem = new Cell(v, nullptr, _first);
    if (!_last)
        _last = elem;
    else
        _first->_previous = elem;
    _first = elem;
}

template<typename T>
T const & List<T>::front() const
{
    return _first->_value;
}

template<typename T>
T& List<T>::front()
{
    return _first->_value;
}

template<typename T>
T const & List<T>::back() const
{
    return _last->_value;
}

template<typename T>
T& List<T>::back()
{
    return _last->_value;
}

template<typename T>
T List<T>::pop_front()
{
    T value = _first->_value;
    Cell* nFirst = _first->_next;
    delete _first;

    _first = nFirst;
    _first->_previous = nullptr;
    return value;
}

template<typename T>
T List<T>::pop_back()
{
    T value = _last->_value;
    Cell* nLast = _last->_previous;
    delete _last;

    _last = nLast;
    _last->_next = nullptr;
    return value;
}

template<typename T>
unsigned int List<T>::size() const
{
    unsigned int s = 0;
    for (Cell* curr = _first; curr != nullptr; curr = curr->_next)
    {
        s++;
    }
    return s;
}

template<typename T>
void List<T>::display(std::ostream & out) const
{
    out << "[ ";
    for (Cell* curr = _first; curr != nullptr; curr = curr->_next)
    {
        out << curr->_value << (curr->_next ? ", " : "");
    }
    out << " ]";
}


// Méthodes de list sur les iterateurs
template<typename T>
typename List<T>::iterator List<T>::begin() const
{
    return iterator(_first);
}

template<typename T>
typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(_first);
}

template<typename T>
typename List<T>::iterator List<T>::end() const
{
    return iterator();
}

template<typename T>
typename List<T>::const_iterator List<T>::cend() const
{
    return const_iterator();
}

template<typename T>
typename List<T>::iterator List<T>::find(T const & elem)
{
    List<T>::iterator it = begin();
    while (*it != elem)
        it++;
    return it;
}

template<typename T>
void List<T>::remove(typename List<T>::iterator const & it)
{
    it._cell->_previous->_next = it._cell->_next;
    it._cell->_previous->_next->_previous = it._cell->_previous;

    delete it._cell;
}

template<typename T>
void List<T>::insert(typename List<T>::iterator const & it, T val)
{
    Cell * nc = new Cell(val, it._cell, it._cell->_next);
    nc->_next->_previous = nc;
    nc->_previous->_next = nc;
}


template<typename T>
std::ostream& operator<<(std::ostream & out, List<T> const & list)
{
    list.display(out);
    return out;
}