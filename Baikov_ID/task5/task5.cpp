#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;


struct Date {
    int year;
    int month;
    int day;
};


struct Seat {
    int wagonNumber;
    int seatNumber;
    string type;
};


struct Ticket {
    Date date;
    int trainNumber;
    Seat seat;
    string passengerName;
};


class Wagon {
public:
    int number;
    string type;
    int capacity;
    vector<bool> availableSeats;

    Wagon(int number, string type, int capacity) : number(number), type(type), capacity(capacity) {
        availableSeats.resize(capacity, true);
    }

    bool isAvailable(int seatNumber) {
        return availableSeats[seatNumber - 1];
    }

    void reserveSeat(int seatNumber) {
        availableSeats[seatNumber - 1] = false;
    }
};

class Train {
public:
    int number;
    string type;
    vector<Wagon> wagons;

    Train() {}

    Train(int number, string type) : number(number), type(type) {}

    void addWagon(Wagon wagon) {
        wagons.push_back(wagon);
    }

    bool hasAvailableSeats(string wagonType, int numSeats) {
        for (Wagon& wagon : wagons) {
            if (wagon.type == wagonType && wagon.availableSeats.size() >= numSeats) {
                int availableCount = 0;
                for (bool available : wagon.availableSeats) {
                    if (available) availableCount++;
                    if (availableCount >= numSeats) return true;
                }
            }
        }
        return false;
    }

    Seat reserveSeats(string wagonType, int numSeats) {
        for (Wagon& wagon : wagons) {
            if (wagon.type == wagonType && wagon.availableSeats.size() >= numSeats) {
                int availableCount = 0;
                for (int i = 0; i < wagon.availableSeats.size(); i++) {
                    if (wagon.availableSeats[i]) availableCount++;
                    if (availableCount == numSeats) {
                        for (int j = i - numSeats + 1; j <= i; j++) {
                            wagon.reserveSeat(j + 1);
                        }
                        return Seat{ wagon.number, i + 1, wagonType };
                    }
                }
            }
        }
        return Seat{ -1, -1, "" }; //if no found
    }
};


class GorkyRailway {
public:
    map<int, Train> trains;
    map<string, double> ticketPrices;

    void addTrain(Train train) {
        trains[train.number] = train;
    }

    void setTicketPrice(string wagonType, double price) {
        ticketPrices[wagonType] = price;
    }
};


class RailwayTicketOffice {
public:
    GorkyRailway& railway;

    RailwayTicketOffice(GorkyRailway& railway) : railway(railway) {}

    bool checkAvailability(Date date, int trainNumber, string wagonType, int numSeats) {
        Train& train = railway.trains[trainNumber];
        return train.hasAvailableSeats(wagonType, numSeats);
    }

    Ticket reserveTicket(Date date, int trainNumber, string wagonType, string passengerName) {
        Train& train = railway.trains[trainNumber];
        Seat seat = train.reserveSeats(wagonType, 1);
        return Ticket{ date, trainNumber, seat, passengerName };
    }

    double calculateTicketPrice(Ticket ticket) {
        return railway.ticketPrices[ticket.seat.type];
    }
};

int main() {
    GorkyRailway gorkyRailway;

    // Adding trains
    for (int i = 1; i <= 3; i++) {
        Train train(i, "Lastochka");
        for (int j = 1; j <= 8; j++) {
            train.addWagon(Wagon(j, "Sitting", 100));
        }
        gorkyRailway.addTrain(train);
    }

    Train firmenny(4, "Firmenny");
    firmenny.addWagon(Wagon(1, "Sitting", 100));
    firmenny.addWagon(Wagon(2, "Sitting", 100));
    for (int i = 3; i <= 8; i++) {
        firmenny.addWagon(Wagon(i, "Compartment", 36));
    }
    for (int i = 9; i <= 12; i++) {
        firmenny.addWagon(Wagon(i, "Platzkart", 54));
    }
    gorkyRailway.addTrain(firmenny);

    Train skory(5, "Skory");
    for (int i = 1; i <= 4; i++) {
        skory.addWagon(Wagon(i, "Compartment", 36));
    }
    for (int i = 5; i <= 12; i++) {
        skory.addWagon(Wagon(i, "Platzkart", 54));
    }
    gorkyRailway.addTrain(skory);

    // Setting ticket prices
    gorkyRailway.setTicketPrice("Sitting", 500);
    gorkyRailway.setTicketPrice("Platzkart", 1000);
    gorkyRailway.setTicketPrice("Compartment", 1500);

    RailwayTicketOffice ticketOffice(gorkyRailway);

    // Example usage
    Date date{ 2024, 11, 15 };
    int trainNumber = 1;
    string wagonType = "Sitting";
    string passengerName = "Ivan Ivanov";

    if (ticketOffice.checkAvailability(date, trainNumber, wagonType, 1)) {
        Ticket ticket = ticketOffice.reserveTicket(date, trainNumber, wagonType, passengerName);
        double price = ticketOffice.calculateTicketPrice(ticket);
        cout << "Ticket reserved!" << endl;
        cout << "Price: " << price << endl;
    }
    else {
        cout << "No available seats." << endl;
    }

    return 0;
}
