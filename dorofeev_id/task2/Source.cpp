#include "MyVector.h"

int main()
{
    try 
    {
        Vector v1(3);
        v1.setComponent(5, 1);
        v1.setComponent(1, 2);
        v1.setComponent(2, 3);

        Vector v2(3);
        v2.setComponent(0, 4);
        v2.setComponent(1, 5);
        v2.setComponent(2, 6);

        std::cout << "v1: " << v1 << std::endl;
        std::cout << "v2: " << v2 << std::endl;

        std::cout << "Size of v1: " << v1.getSize() << std::endl;
        std::cout << "Size of v2: " << v2.getSize() << std::endl;

        std::cout << "v1 + v2: " << Vector::sum(v1, v2) << std::endl;

        std::cout << "Scalar product of v1 and v2: " << Vector::dotProduct(v1, v2) << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    system("pause");
    return 0;
}