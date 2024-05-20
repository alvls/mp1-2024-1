#include "Ticket.h"

Ticket::Ticket(std::string _date, int _trainNumber, int _carriageNumber, int _seatNumber, SeatType _seatType, TrainType _trainType,
std::string _passengerName, std::string _departureStation, std::string _arrivalStation)
    : date(_date), trainNumber(_trainNumber), carriageNumber(_carriageNumber), seatNumber(_seatNumber),
    seatType(_seatType), trainType(_trainType), passengerName(_passengerName), departureStation(_departureStation), arrivalStation(_arrivalStation),
    reserved(false) {}

std::string Ticket::getDate() const 
{
    return date;
}

int Ticket::getTrainNumber() const 
{
    return trainNumber;
}

int Ticket::getCarriageNumber() const 
{
    return carriageNumber;
}

int Ticket::getSeatNumber() const 
{
    return seatNumber;
}

SeatType Ticket::getSeatType() const 
{
    return seatType;
}

TrainType Ticket::getTrainType() const 
{
    return trainType;
}

std::string Ticket::getPassengerName() const 
{
    return passengerName;
}

std::string Ticket::getDepartureStation() const 
{
    return departureStation;
}

std::string Ticket::getArrivalStation() const 
{
    return arrivalStation;
}

bool Ticket::isReserved() const 
{
    return reserved;
}

void Ticket::setReserved(bool value) 
{
    reserved = value;
}

double Ticket::calculateTicketPrice() const 
{
    // Define pricing scheme based on seat type and train type
    double price = 0.0;
    switch (seatType) 
    {
    case SeatType::SITTING:
        switch (trainType) 
        {
        case TrainType::LASTOCHKA:
            price = 30.0; // Example price for sitting seat on Lastochka train
            break;
        case TrainType::BRANDED:
            price = 40.0; // Example price for sitting seat on branded train
            break;
        case TrainType::EXPRESS:
            price = 35.0; // Example price for sitting seat on express train
            break;
        }
        break;
    case SeatType::SLEEPING:
        switch (trainType) 
        {
        case TrainType::BRANDED:
            price = 100.0; // Example price for sleeping seat on branded train
            break;
        case TrainType::EXPRESS:
            price = 90.0; // Example price for sleeping seat on express train
            break;
        default:
            // No sleeping seats available on other trains
            price = 0.0;
            break;
        }
        break;
    case SeatType::COMPARTMENT:
        switch (trainType) 
        {
        case TrainType::BRANDED:
            price = 50.0; // Example price for compartment seat on branded train
            break;
        case TrainType::EXPRESS:
            price = 45.0; // Example price for compartment seat on express train
            break;
        default:
            // No compartment seats available on other trains
            price = 0.0;
            break;
        }
        break;
    case SeatType::SV:
        switch (trainType) 
        {
        case TrainType::BRANDED:
            price = 150.0; // Example price for SV seat on branded train
            break;
        default:
            // No SV seats available on other trains
            price = 0.0;
            break;
        }
        break;
    }
    return price;
}
