#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>

class Vector 
{
private:
    int size;
    int* elements;

public:
    Vector();
    explicit Vector(int sz);
    Vector(const Vector& other);
    ~Vector();
    Vector& operator=(const Vector& other);
    void setComponent(int index, int value);
    int getComponent(int index) const;
    int getSize() const;
    double length() const;
    static int dotProduct(const Vector& v1, const Vector& v2);
    static Vector sum(const Vector& v1, const Vector& v2);
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec);
};

