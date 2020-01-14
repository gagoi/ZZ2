#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <exception>

class Vector
{
public:
    Vector();
    Vector(const Vector& v);
    Vector(int capa);
    ~Vector();

    void push_back(double elem);
    int getCapacity() const;
    int getSize() const;
    double& at(int index);
    double at(int index) const;
    double& operator[](int index);
    double operator[](int index) const;
    Vector& operator=(const Vector& otherV);

private:
    double* _tab;
    int _capacity;
    int _size;
};

std::ostream& operator<<(std::ostream& out, const Vector& v);
Vector operator+(const Vector& v1, const Vector& v2);

#endif