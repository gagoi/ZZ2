#include "Pile.hpp"

Pile::Pile() :
    _tab(nullptr),
    _max_size(DEFAULT_SIZE),
    _size(0)
{
    try {
        _tab = new int[_max_size];
    } catch (const std::bad_alloc& e) {
        throw e;
    }
}

Pile::Pile(int s) :
    _tab(nullptr),
    _max_size(s),
    _size(0)
{
    if (_max_size > 0)
    {
        try {
            _tab = new int[_max_size];
        } catch (const std::bad_alloc& e) {
            throw e;
        }
    }
    else
    {
        throw std::invalid_argument("Taille de pile invalide");
    }
}

Pile::Pile(const Pile& o) :
    _tab(nullptr),
    _max_size(o._max_size),
    _size(o._size)
{
    try {
        _tab = new int[_max_size];
        std::copy(_tab, _tab + _size, o._tab);
    } catch (const std::bad_alloc& e) {
        throw e;
    }
}

Pile::~Pile()
{
    delete[] _tab;
}

Pile& Pile::operator=(const Pile& o)
{
    if (this != &o)
    {
        _max_size = o._max_size;
        _size = o._size;
        try {
            _tab = new int[_max_size];
            std::copy(_tab, _tab + _size, o._tab);
        } catch (const std::bad_alloc& e) {
            throw e;
        }
    }
    return *this;
}

bool Pile::empty() const
{
    return _size == 0;
}

void Pile::push(int elem)
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

void Pile::pop()
{
    if (_size > 0)
        _size--;
    else
        throw std::invalid_argument("Aucun element dans la pile");
}

int Pile::top() const
{
    return _tab[_size - 1];
}

int Pile::size() const
{
    return _size;
}