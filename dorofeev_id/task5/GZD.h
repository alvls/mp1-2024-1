#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "Ticket.h"


class GorkyRailway
{
private:
    std::unordered_map<int, std::vector<Ticket>> tickets;

public:
    bool checkAvailability(int trainNumber, SeatType seatType, int numTickets);
    bool reserveSeats(int trainNumber, SeatType seatType, int numTickets);
    double calculateTotalCost(int trainNumber, TrainType trainType, SeatType seatType, int numTickets);
    bool cancelTicketOrder(int trainNumber, SeatType seatType, int numTickets);
    void generateTicketsToFile(const std::string& filename);
    std::vector<Ticket> getReservedTickets(int trainNumber, SeatType seatType, int numTickets);

    void generateLastochkaTickets(int numTrainsPerDay, int numCarsPerTrain, int numSeatsPerCar);
    void generateBrandedTickets(int numTrainsPerDay, int numSVCars, int numCompartmentCars, int numReservedCars,
        int numSeatsPerSV, int numSeatsPerCompartment, int numSeatsPerReserved);
    void generateExpressTickets(int numTrainsPerDay, int numCarsPerTrain, int numSeatsPerCar);
    void populateTickets();

private:
    int getRandomInt(int min, int max);
};
