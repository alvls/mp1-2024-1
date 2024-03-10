#include "Vect.h"

using namespace std;

vect::vect(unsigned size_) {
    // size - unsigned, so we dont need to check if size_ > 0
    size = size_;
    if (size < 2) { // Error
        size = 2; 
    }
    if (size > 20) { // Error
        size = 20; 
    }
    coords = new double[size] {0};
}

vect::vect(const vect& v) {
    size = v.size;
    coords = new double[size] {0};
    for (unsigned i = 0; i < size; i++) {
        coords[i] = v.coords[i];
    }
}

vect::~vect() {
    delete [] coords;
}

unsigned vect::getSize() {
    return size;
}

bool vect::setCoord(double coord, unsigned pos) {
    if ((pos >= size) || (pos < 0)) { // Error
        return false;
    }
    coords[pos] = coord;
    return true;
};


double vect::getCoord(unsigned pos) {
    if ((pos >= size) || (pos < 0)) { // Error
        return NULL;
    }
    return coords[pos];
}

double vect::getLen() {
    double len = 0.0;
    for (unsigned i = 0; i < size; i++) {
        len += coords[i] * coords[i];
    }
    len = sqrt(len);
    return len;
}

vect& vect::operator= (vect v) {
    if (size != v.size) { // Error
        return *this;
    }
    size = v.size;
    coords = new double[size] {0};
    for (unsigned i = 0; i < size; i++) {
        coords[i] = v.coords[i];
    }
    return *this;
}

vect vect::operator+ (vect v2) {
    if (size != v2.size) { // Error
        return *this;
    }
    vect v(size);
    for (unsigned i = 0; i < size; i++) {
        v.coords[i] = coords[i] + v2.coords[i];
    }
    return v;
}

vect vect::operator+= (vect v2) {
    if (size != v2.size) { // Error
        return *this;
    }
    for (unsigned i = 0; i < size; i++) {
        coords[i] += v2.coords[i];
    }
    return *this;
}

vect vect::operator-= (vect v2) {
    if (size != v2.size) { // Error
        return *this;
    }
    for (unsigned i = 0; i < size; i++) {
        coords[i] -= v2.coords[i];
    }
    return *this;
}

vect vect::operator- (vect v2) {
    if (size != v2.size) { // Error
        return *this;
    }
    vect v(size);
    for (unsigned i = 0; i < size; i++) {
        v.coords[i] = coords[i] - v2.coords[i];
    }
    return v;
}

double vect::operator* (vect v2) {
    if (size != v2.size) { // Error
        return NULL;
    }
    double sclr = 0;
    for (unsigned i = 0; i < size; i++) {
        sclr += coords[i] * v2.coords[i];
    }
    return sclr;
}

vect vect::operator* (double k) {
    vect v(size);
    for (unsigned i = 0; i < size; i++) {
        v.coords[i] = coords[i] * k;
    }
    return v;
}

void vect::printVect() {
    for (unsigned i = 0; i < size; i++) {
        cout << "Coordinate_" << i << "  " << coords[i] << endl;
    }
}