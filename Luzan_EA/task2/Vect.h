#pragma once
#include <iostream>
#include <cmath>


class vect
{
private:
    double* coords;
    unsigned size;

public:
    vect(unsigned size_);

    vect(const vect& v);

    ~vect();

    unsigned getSize();

    bool setCoord(double coord, unsigned pos);

    double getCoord(unsigned pos);

    double getLen();

    vect& operator= (vect v);

    vect operator+ (vect v2);

    vect operator* (vect v2);

    vect operator* (double k);

    void printVect();

};