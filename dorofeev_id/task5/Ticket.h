#pragma once

#include <string>

enum class SeatType { SITTING, SLEEPING, COMPARTMENT, SV };
enum class TrainType { LASTOCHKA, BRANDED, EXPRESS };

class Ticket {
private:
    std::string date;
    int trainNumber;
    int carriageNumber;
    int seatNumber;
    SeatType seatType;
    TrainType trainType; // New member variable to represent the type of train
    std::string passengerName;
    std::string departureStation;
    std::string arrivalStation;
    bool reserved;

public:
    Ticket(std::string _date, int _trainNumber, int _carriageNumber, int _seatNumber, SeatType _seatType, TrainType _trainType,
        std::string _passengerName, std::string _departureStation, std::string _arrivalStation);

    // Getters
    std::string getDate() const;
    int getTrainNumber() const;
    int getCarriageNumber() const;
    int getSeatNumber() const;
    SeatType getSeatType() const;
    TrainType getTrainType() const;
    std::string getPassengerName() const;
    std::string getDepartureStation() const;
    std::string getArrivalStation() const;
    bool isReserved() const;
    void setReserved(bool value);

    double calculateTicketPrice() const;
};
