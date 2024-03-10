#include <iostream>
#include <vector>
#include <cmath>

class Vector {
private:
    std::vector<int> components;

public:
    Vector() {}

    Vector(int size, int defaultValue = 0) : components(size, defaultValue) {}

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            components = other.components;
        }
        return *this;
    }

    void resize(int size) {
        components.resize(size);
    }

    int size() const {
        return components.size();
    }

    void setComponent(int index, int value) {
        if (index >= 0 && index < size()) {
            components[index] = value;
        }
    }

    int getComponent(int index) const {
        if (index >= 0 && index < size()) {
            return components[index];
        }
        else {
            return 0;
        }
    }

    double length() const {
        double sum = 0.0;
        for (int value : components) {
            sum += static_cast<double>(value * value);
        }
        return std::sqrt(sum);
    }

    int scalarProduct(const Vector& other) const {
        if (size() != other.size()) {
            return 0;
        }

        int result = 0;
        for (int i = 0; i < size(); ++i) {
            result += components[i] * other.getComponent(i);
        }
        return result;
    }

    Vector sum(const Vector& other) const {
        if (size() != other.size()) {
            return Vector();
        }

        Vector result(size());
        for (int i = 0; i < size(); ++i) {
            result.setComponent(i, components[i] + other.getComponent(i));
        }
        return result;
    }

    void display() const {
        for (int value : components) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Vector vector1(3, 1);
    Vector vector2(3, 2);

    std::cout << "Vector 1: ";
    vector1.display();

    std::cout << "Vector 2: ";
    vector2.display();

    std::cout << "Vector 1 length: " << vector1.length() << std::endl;
    std::cout << "Vector 2 length: " << vector2.length() << std::endl;

    std::cout << "Scalar product: " << vector1.scalarProduct(vector2) << std::endl;

    Vector sum = vector1.sum(vector2);
    std::cout << "Sum of vectors: ";
    sum.display();

    Vector myVector(5);

    for (int i = 0; i < myVector.size(); ++i) {
        myVector.setComponent(i, i + 1);
    }

    myVector.display();

    for (int i = 0; i < myVector.size(); ++i) {
        std::cout << "Component " << i << ": " << myVector.getComponent(i) << std::endl;
    }

    return 0;
}