#include "TicketOffice.h"

//////////////////////////////////////////////////////////////////////////////////////////Train methods////////////////////////////////////////////////////////////////////////////////////////////////////
Train::Train(int num, std::string dep, std::string arr) : number(num), departureStation(dep), arrivalStation(arr) {}

void Train::addWagon(Wagon wagon) 
{
    wagons.push_back(wagon);
}

int Train::getNumber() const
{
    return number;
}

std::string Train::getDepartureStation() const 
{
    return departureStation;
}

std::string Train::getArrivalStation() const 
{
    return arrivalStation;
}

const std::vector<Wagon>& Train::getWagons() const 
{
    return wagons;
}

//////////////////////////////////////////////////////////////////////////////////////////Wagon methods////////////////////////////////////////////////////////////////////////////////////////////////////
Wagon::Wagon(int num, std::string t, int s) : number(num), type(t), seats(s) {}

int Wagon::getNumber() const 
{
    return number;
}

std::string Wagon::getType() const 
{
    return type;
}

int Wagon::getSeats() const 
{
    return seats;
}

//////////////////////////////////////////////////////////////////////////////////////////Ticket methods////////////////////////////////////////////////////////////////////////////////////////////////////
Ticket::Ticket(std::string d, int tNum, int wNum, int sNum, std::string name)
    : date(d), trainNumber(tNum), wagonNumber(wNum), seatNumber(sNum), passengerName(name) {}

std::string Ticket::getDate() const 
{
    return date;
}

int Ticket::getTrainNumber() const 
{
    return trainNumber;
}

int Ticket::getWagonNumber() const 
{
    return wagonNumber;
}

int Ticket::getSeatNumber() const 
{
    return seatNumber;
}

std::string Ticket::getPassengerName() const 
{
    return passengerName;
}

//////////////////////////////////////////////////////////////////////////////////////////GZD methods////////////////////////////////////////////////////////////////////////////////////////////////////
void GZD::addTrain(Train train) 
{
    trains.push_back(train);
}

void GZD::addTicket(Ticket ticket) 
{
    tickets.push_back(ticket);
}

const std::vector<Train>& GZD::getTrains() const 
{
    return trains;
}

const std::vector<Ticket>& GZD::getTickets() const 
{
    return tickets;
}

//////////////////////////////////////////////////////////////////////////////////////////GZD methods////////////////////////////////////////////////////////////////////////////////////////////////////
RailwayTicketOffice::RailwayTicketOffice(GZD& s) : station(s) {}

