#include "RailwayTicketOffice.h"

RailwayTicketOffice::RailwayTicketOffice(GorkyRailway& _railway) : railway(_railway) {}

bool RailwayTicketOffice::acceptBuyerData(std::string date, int trainNumber, SeatType seatType, int numTickets, std::string passengerName) 
{
    // Check availability and reserve seats
    bool isAvailable = checkAvailability(trainNumber, seatType, numTickets);
    if (isAvailable) 
{
        return reserveSeats(trainNumber, seatType, numTickets);
    }
    return false;
}

bool RailwayTicketOffice::checkAvailability(int trainNumber, SeatType seatType, int numTickets) 
{
    return railway.checkAvailability(trainNumber, seatType, numTickets);
}

bool RailwayTicketOffice::reserveSeats(int trainNumber, SeatType seatType, int numTickets) 
{
    return railway.reserveSeats(trainNumber, seatType, numTickets);
}

double RailwayTicketOffice::calculateTotalCost(int trainNumber, TrainType trainType, SeatType seatType, int numTickets)
{
    return railway.calculateTotalCost(trainNumber, trainType, seatType, numTickets);
}

bool RailwayTicketOffice::cancelTicketOrder(int trainNumber, SeatType seatType, int numTickets) 
{
    return railway.cancelTicketOrder(trainNumber, seatType, numTickets);
}

void RailwayTicketOffice::generateTickets() 
{
    railway.generateTicketsToFile("Tickets.txt");
}
