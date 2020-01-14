#include "Pile.hpp"

template<typename T>
Pile<T>::Pile() :
    _tab(nullptr),
    _max_size(DEFAULT_SIZE),
    _size(0)
{
    _tab = new T[_max_size];
}

template<typename T>
Pile<T>::Pile(int s) :
    _tab(nullptr),
    _max_size(s),
    _size(0)
{
    if (_max_size > 0)
    {
        _tab = new T[_max_size];
    }
    else
    {
        throw std::invalid_argument("Taille de pile invalide");
    }
}

template<typename T>
Pile<T>::Pile(const Pile<T>& o) :
    _tab(nullptr),
    _max_size(o._max_size),
    _size(o._size)
{
    _tab = new T[_max_size];
    std::copy(_tab, _tab + _size, o._tab);
}

template<typename T>
Pile<T>::~Pile()
{
    delete[] _tab;
}

template<typename T>
Pile<T>& Pile<T>::operator=(const Pile<T>& o)
{
    if (this != &o)
    {
        _max_size = o._max_size;
        _size = o._size;

        _tab = new T[_max_size];
        std::copy(_tab, _tab + _size, o._tab);
    }
    return *this;
}

template<typename T>
bool Pile<T>::empty() const
{
    return _size == 0;
}

template<typename T>
void Pile<T>::push(T elem)
{
    if (_size < _max_size)
    {
        _tab[_size] = elem;
        _size++;
    }
    else
    {
        throw std::out_of_range("Taille de pile max atteinte");
    }
}

template<typename T>
void Pile<T>::pop()
{
    if (_size > 0)
        _size--;
    else
        throw std::invalid_argument("Aucun element dans la pile");
}

template<typename T>
int Pile<T>::top() const
{
    return _tab[_size - 1];
}

template<typename T>
int Pile<T>::size() const
{
    return _size;
}