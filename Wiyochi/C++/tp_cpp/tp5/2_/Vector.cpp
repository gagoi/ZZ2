#include "Vector.hpp"

Vector::Vector() :
    _tab(nullptr),
    _capacity(10),
    _size(0)
{
    _tab = new double[_capacity];
}

Vector::Vector(const Vector& v) :
    _tab(nullptr),
    _capacity(v.getCapacity()),
    _size(v.getSize())
{
    _tab = new double[_capacity];
    std::copy(_tab, _tab+_size, v._tab);
}

Vector::Vector(int capa) :
    _tab(nullptr),
    _capacity(capa > 0 ? capa : 10),
    _size(0)
{
    _tab = new double[_capacity];
}

Vector::~Vector()
{
    delete[] _tab;
}

void Vector::push_back(double elem)
{
    if (_size < _capacity)
    {
        _tab[_size] = elem;
    }
    else
    {
        double* buffer = new double[_size];
        std::copy(_tab, _tab+_size, buffer);
        delete[] _tab;
        _capacity *= 2;
        _tab = new double[_capacity];
        std::copy(buffer, buffer + _size, _tab);
        delete[] buffer;
    }
    _size++;
}

int Vector::getCapacity() const
{
    return _capacity;
}

int Vector::getSize() const
{
    return _size;
}

double& Vector::at(int index)
{
    return _tab[index];
}

double Vector::at(int index) const
{
    return _tab[index];
}

double& Vector::operator[](int index)
{
    return at(index);
}

double Vector::operator[](int index) const
{
    return at(index);
}

Vector& Vector::operator=(const Vector& otherV)
{
    if(&otherV != this)
    {
        delete[] _tab;
        _capacity = otherV.getCapacity();
        _tab = new double[_capacity];

        for (int i = 0; i < _capacity; i++)
            _tab[i] = otherV[i];
    }
    
    return *this;
}


std::ostream& operator<<(std::ostream& out, const Vector& v)
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

Vector operator+(const Vector& v1, const Vector& v2)
{
    Vector vresult(v1.getCapacity() + v2.getCapacity());
    for (int i = 0; i < v1.getSize(); i++)
        vresult.push_back(v1[i]);
    for (int i = 0; i < v2.getSize(); i++)
        vresult.push_back(v2[i]);
    return vresult;
}