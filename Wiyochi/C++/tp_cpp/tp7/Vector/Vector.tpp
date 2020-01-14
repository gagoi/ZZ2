#include "Vector.hpp"

template<typename T>
Vector<T>::Vector() :
    _tab(nullptr),
    _capacity(10),
    _size(0)
{
    _tab = new T[_capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v) :
    _tab(nullptr),
    _capacity(v.getCapacity()),
    _size(v.getSize())
{
    if (_capacity > 0)
    {
        _tab = new T[_capacity];
        std::copy(_tab, _tab+_size, v._tab);
    }
    else
    {
        throw std::invalid_argument("Vector capacity invalid");
    }
    
}

template<typename T>
Vector<T>::Vector(int capa) :
    _tab(nullptr),
    _capacity(capa > 0 ? capa : 10),
    _size(0)
{
    _tab = new T[_capacity];
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] _tab;
}

template<typename T>
void Vector<T>::push_back(T elem)
{
    if (_size < _capacity)
    {
        _tab[_size] = elem;
        _size++;
    }
    else
    {
        _capacity *= 2;
        T* buffer = new T[_capacity];
        std::copy(buffer, buffer+_size, _tab);
        _size++;

        delete[] _tab;
        _tab = buffer;        
    }
}

template<typename T>
int Vector<T>::getCapacity() const
{
    return _capacity;
}

template<typename T>
int Vector<T>::getSize() const
{
    return _size;
}

template<typename T>
T& Vector<T>::at(int index)
{
    return _tab[index];
}

template<typename T>
T Vector<T>::at(int index) const
{
    return _tab[index];
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    return at(index);
}

template<typename T>
T Vector<T>::operator[](int index) const
{
    return at(index);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& otherV)
{
    if(&otherV != this)
    {
        delete[] _tab;
        _capacity = otherV.getCapacity();
        _tab = new T[_capacity];

        for (int i = 0; i < _capacity; i++)
            _tab[i] = otherV[i];
    }
    
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v)
{
    if(v.getSize())
    {
        out << "[";
        for (int i = 0; i < v.getSize() - 1; i++)
            out << v[i] << ",";
        out << v[v.getSize() - 1] << "]";
    }
    return out;
}

template<typename T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2)
{
    Vector<T> vresult(v1.getCapacity() + v2.getCapacity());
    for (int i = 0; i < v1.getSize(); i++)
        vresult.push_back(v1[i]);
    for (int i = 0; i < v2.getSize(); i++)
        vresult.push_back(v2[i]);
    return vresult;
}