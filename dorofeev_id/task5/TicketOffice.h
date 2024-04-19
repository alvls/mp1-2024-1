#pragma once
#include <iostream>
#include <vector>
#include <string>

class Wagon
{
private:
    int number;
    std::string type;
    int seats;

public:
    Wagon(int num, std::string t, int s);
    int getNumber() const;
    std::string getType() const;
    int getSeats() const;
};

class Train
{
private:
    int number;
    std::string departureStation;
    std::string arrivalStation;
    std::vector<Wagon> wagons;

public:
    Train::Train(int num, std::string dep, std::string arr);
    void Train::addWagon(Wagon wagon);
    int Train::getNumber() const;
    std::string Train::getDepartureStation() const;
    std::string Train::getArrivalStation() const;
    const std::vector<Wagon>& Train::getWagons() const;
};

class Ticket 
{
private:
    std::string date;
    int trainNumber;
    int wagonNumber;
    int seatNumber;
    std::string passengerName;

public:
    Ticket(std::string d, int tNum, int wNum, int sNum, std::string name);
    std::string getDate() const;
    int getTrainNumber() const;
    int getWagonNumber() const;
    int getSeatNumber() const;
    std::string getPassengerName() const;
};

class GZD 
{
private:
    std::vector<Train> trains;
    std::vector<Ticket> tickets;
public:
    void addTrain(Train train);
    void addTicket(Ticket ticket);
    const std::vector<Train>& getTrains() const;
    const std::vector<Ticket>& getTickets() const;
};

class RailwayTicketOffice 
{
private:
    GZD& station;

public:
    RailwayTicketOffice(GZD& s);
};