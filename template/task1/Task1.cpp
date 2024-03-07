#include <iostream>
#include <iomanip>

class WeightConverter {
private:
    double weight_kg;
    const double apothecary_pound = 0.373242;
    const double troy_ounce = 0.031103;
    const double pound = 0.453592;
    const double ounce = 0.02835;
    const double stone = 6.350295;
    const double newtons = 0.101972;
    const double slug = 14.593903;
    const double gram = 0.001;

public:
    WeightConverter(double weight_kg) : weight_kg(weight_kg) {}

    void setWeight(double weight_kg) {
        this->weight_kg = weight_kg;
    }

    double getWeight() const {
        return weight_kg;
    }

    double toApothecaryPounds() const {
        return weight_kg / apothecary_pound;
    }

    double toTroyOunces() const {
        return weight_kg / troy_ounce;
    }

    double toPounds() const {
        return weight_kg / pound;
    }

    double toOunces() const {
        return weight_kg / ounce;
    }

    double toStones() const {
        return weight_kg / stone;
    }

    double toNewtons() const {
        return weight_kg / newtons;
    }

    double toSlugs() const {
        return weight_kg / slug;
    }

    double toGrams() const {
        return weight_kg / gram;
    }

    friend std::ostream& operator<<(std::ostream& os, const WeightConverter& wc) {
        os << std::fixed << std::setprecision(2) << wc.weight_kg << " kg";
        return os;
    }
};

int main() {
    double userWeight;
    
    std::cout << "Enter the weight in kilograms: ";
    std::cin >> userWeight;

    WeightConverter wc(userWeight);

    int choice;
    
    do {
        system("clear");

        std::cout << "Current weight: " << wc << std::endl;

        std::cout << "\nChoose an option:\n";
        std::cout << "1. Convert to Apothecary Pounds\n";
        std::cout << "2. Convert to Troy Ounces\n";
        std::cout << "3. Convert to Pounds\n";
        std::cout << "4. Convert to Ounces\n";
        std::cout << "5. Convert to Stones\n";
        std::cout << "6. Convert to Newtons\n";
        std::cout << "7. Convert to Slugs\n";
        std::cout << "8. Convert to Grams\n";
        std::cout << "9. Change Weight\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Weight in Apothecary Pounds: " << wc.toApothecaryPounds() << std::endl;
                break;
            case 2:
                std::cout << "Weight in Troy Ounces: " << wc.toTroyOunces() << std::endl;
                break;
            case 3:
                std::cout << "Weight in Pounds: " << wc.toPounds() << std::endl;
                break;
            case 4:
                std::cout << "Weight in Ounces: " << wc.toOunces() << std::endl;
                break;
            case 5:
                std::cout << "Weight in Stones: " << wc.toStones() << std::endl;
                break;
            case 6:
                std::cout << "Weight in Pound Mass: " << wc.toNewtons() << std::endl;
                break;
            case 7:
                std::cout << "Weight in Slugs: " << wc.toSlugs() << std::endl;
                break;
            case 8:
                std::cout << "Weight in Grams: " << wc.toGrams() << std::endl;
                break;
            case 9:
                std::cout << "Enter the new weight in kilograms: ";
                std::cin >> userWeight;
                wc.setWeight(userWeight);
                break;
            case 0:
                std::cout << "Exiting program...\n";
                break;
            default:
                system("clear"); 
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
        
        if (choice != 0 && choice != 9) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (choice != 0);

    return 0;
}
