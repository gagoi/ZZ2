#ifndef VECTOR_GEN_HPP
#define VECTOR_GEN_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <exception>

template<typename T>
class Vector
{
public:
    Vector();
    Vector(const Vector<T>& v);
    Vector(int capa);
    ~Vector();

    void push_back(T elem);
    int getCapacity() const;
    int getSize() const;
    T& at(int index);
    T at(int index) const;
    T& operator[](int index);
    T operator[](int index) const;
    Vector<T>& operator=(const Vector<T>& otherV);

private:
    T* _tab;
    int _capacity;
    int _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v);

template<typename T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2);

#include "Vector.tpp"

#endif