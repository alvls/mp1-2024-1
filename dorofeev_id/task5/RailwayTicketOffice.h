#pragma once

#include <string>
#include <vector>
#include "GZD.h"

class RailwayTicketOffice {
private:
    GorkyRailway& railway;

public:
    RailwayTicketOffice(GorkyRailway& _railway);
    bool acceptBuyerData(std::string date, int trainNumber, SeatType seatType, int numTickets, std::string passengerName);
    bool checkAvailability(int trainNumber, SeatType seatType, int numTickets);
    bool reserveSeats(int trainNumber, SeatType seatType, int numTickets);
    double calculateTotalCost(int trainNumber, TrainType trainType, SeatType seatType, int numTickets);
    bool cancelTicketOrder(int trainNumber, SeatType seatType, int numTickets);
    void generateTickets();
};
