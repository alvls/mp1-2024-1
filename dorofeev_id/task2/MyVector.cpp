#include "MyVector.h"

Vector::Vector() : size(0), elements(nullptr) {}

Vector::Vector(int sz) : size(sz) 
{
    if (sz < 1 || sz > 20)
        throw std::invalid_argument("The vector size should be from 1 to 20");
    elements = new int[size];
}

Vector::Vector(const Vector& other) : size(other.size) 
{
    elements = new int[size];
    for (int i = 0; i < size; ++i)
        elements[i] = other.elements[i];
}

Vector::~Vector() 
{
    delete[] elements;
}

Vector& Vector::operator=(const Vector& other) 
{
    if (this != &other) 
    {
        delete[] elements;
        size = other.size;
        elements = new int[size];
        for (int i = 0; i < size; ++i)
            elements[i] = other.elements[i];
    }
    return *this;
}

void Vector::setComponent(int index, int value) 
{
    if (index < 0 || index >= size)
        throw std::out_of_range("The index goes beyond the boundaries of the vector");
    elements[index] = value;
}

int Vector::getComponent(int index) const 
{
    if (index < 0 || index >= size)
        throw std::out_of_range("The index goes beyond the boundaries of the vector");
    return elements[index];
}

int Vector::getSize() const 
{
    return size;
}

double Vector::length() const
{
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
        sum += elements[i] * elements[i];
    return sqrt(sum);
}

int Vector::dotProduct(const Vector& v1, const Vector& v2) 
{
    if (v1.size != v2.size)
        throw std::invalid_argument("The sizes of the vectors must be the same");
    int result = 0;
    for (int i = 0; i < v1.size; ++i)
        result += v1.elements[i] * v2.elements[i];
    return result;
}

Vector Vector::sum(const Vector& v1, const Vector& v2) 
{
    if (v1.size != v2.size)
        throw std::invalid_argument("The sizes of the vectors must be the same");
    Vector result(v1.size);
    for (int i = 0; i < v1.size; ++i)
        result.elements[i] = v1.elements[i] + v2.elements[i];
    return result;
}

std::ostream& operator<<(std::ostream& out, const Vector& vec) 
{
    out << "(";
    for (int i = 0; i < vec.getSize(); ++i) 
    {
        out << vec.getComponent(i);
        if (i != vec.getSize() - 1)
            out << ", ";
    }
    out << ")";
    return out;
}
