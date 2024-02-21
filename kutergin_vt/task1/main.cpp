#include <iostream>

class weight_converter {
private:
    double w_kg; // вес в кг

public:
    weight_converter (double w_kg2) // конструктор преобразования
    {
        w_kg = w_kg2;
    }
    weight_converter () // конструктор по умолчанию
    {
        w_kg = 0.0;
    }
    void setWeight(double newValue) // установить вес в кг
    {
        w_kg = newValue;
    }
    double kg() // kilograms
    {
        return w_kg;
    }
    double kg_pharmacyPound() // kilograms to a pharmacy pound (troy pound)
    {
        return w_kg * 2.67922888;
    }
    double kg_troyOunce() // kilograms to troy ounce
    {
        return w_kg * 32.15074656;
    }
    double kg_pood() //kilograms to poods
    {
        return w_kg * 0.06104821;
    }
    double kg_pound() //kilograms to pounds
    {
        return w_kg * 2.20462262;
    }
    double kg_ounce() // kilograms to ounces
    {
        return w_kg * 35.27396194;
    }
    double kg_carat() // kilograms to carats
    {
        return w_kg * 5000.0;
    }
    double kg_grain() //kilograms to grains
    {
        return w_kg * 15432.3583529;
    }
    double kg_livr() // kilograms to livres
    {
        return w_kg * 2.04290091;
    }
    double kg_zolotnik() // kilograms to zolotnik
    {
        return w_kg * 234.42513012;
    }

    void show_kg()
    {
        std::cout << std::fixed << kg() << " kilograms" << std::endl;
    }
    void show_pharmacyPoun()
    {
        std::cout << std::fixed << kg_pharmacyPound() << " pharmacy pounds" << std::endl;
    }
    void show_troyOunce()
    {
        std::cout << std::fixed << kg_troyOunce() << " troy ounces" << std::endl;
    }
    void show_pood()
    {
        std::cout << std::fixed << kg_pood() << " poods" << std::endl;
    }
    void show_pound()
    {
        std::cout << std::fixed << kg_pound() << " pounds" << std::endl;
    }
    void show_ounce()
    {
        std::cout << std::fixed << kg_ounce() << " ounces" << std::endl;
    }
    void show_carat()
    {
        std::cout << std::fixed << kg_carat() << " carats" << std::endl;
    }
    void show_grain()
    {
        std::cout << std::fixed << kg_grain() << " grains" << std::endl;
    }
    void show_livr()
    {
        std::cout << std::fixed << kg_livr() << " livres" << std::endl;
    }
    void show_zolotnik()
    {
        std::cout << std::fixed << kg_zolotnik() << " zolotniks" << std::endl;
    }
};

int main() {
    weight_converter conv;
    conv = weight_converter(65.0);
    conv.show_kg();
    conv.show_pound();
    conv.setWeight(66.0);
    conv.show_kg();
    conv.show_zolotnik();
    conv.show_carat();
}

