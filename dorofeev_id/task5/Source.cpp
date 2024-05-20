#include <iostream>
#include <fstream>
#include "GZD.h"

void displayTickets(const std::vector<Ticket>& tickets) 
{
    std::cout << "Purchased Tickets:" << std::endl;
    for (const auto& ticket : tickets) 
    {
        std::cout << "Date: " << ticket.getDate() << ", Train Number: " << ticket.getTrainNumber()
            << ", Carriage Number: " << ticket.getCarriageNumber() << ", Seat Number: " << ticket.getSeatNumber()
            << ", Passenger Name: " << ticket.getPassengerName() << ", Departure Station: " << ticket.getDepartureStation()
            << ", Arrival Station: " << ticket.getArrivalStation() << std::endl;
    }
    std::cout << std::endl;
}

int main() 
{
    // Create GorkyRailway instance
    GorkyRailway railway;

    // Generate some tickets
    railway.generateLastochkaTickets(2, 8, 100);
    railway.generateBrandedTickets(2, 2, 6, 4, 18, 18, 27);
    railway.generateExpressTickets(2, 8, 100);

    // Simulate purchasing tickets
    std::vector<Ticket> purchasedTickets;

    // Example purchase: 3 Lastochka sitting seats
    if (railway.checkAvailability(1, SeatType::SITTING, 3)) 
    {
        if (railway.reserveSeats(1, SeatType::SITTING, 3)) 
        {
            std::cout << "Successfully reserved 3 sitting seats on Lastochka train." << std::endl;
            std::vector<Ticket> lastochkaSittingTickets = railway.getReservedTickets(1, SeatType::SITTING, 3);
            purchasedTickets.insert(purchasedTickets.end(), lastochkaSittingTickets.begin(), lastochkaSittingTickets.end());
        }
        else 
        {
            std::cout << "Failed to reserve seats on Lastochka train." << std::endl;
        }
    }
    else 
    {
        std::cout << "Not enough sitting seats available on Lastochka train." << std::endl;
    }

    // Example purchase: 2 branded SV seats
    if (railway.checkAvailability(1, SeatType::SV, 2)) 
    {
        if (railway.reserveSeats(1, SeatType::SV, 2)) 
        {
            std::cout << "Successfully reserved 2 SV seats on branded train." << std::endl;
            std::vector<Ticket> brandedSvTickets = railway.getReservedTickets(1, SeatType::SV, 2);
            purchasedTickets.insert(purchasedTickets.end(), brandedSvTickets.begin(), brandedSvTickets.end());
        }
        else 
        {
            std::cout << "Failed to reserve SV seats on branded train." << std::endl;
        }
    }
    else 
    {
        std::cout << "Not enough SV seats available on branded train." << std::endl;
    }

    // Display purchased tickets
    displayTickets(purchasedTickets);

    // Write purchased tickets to a file
    std::ofstream outFile("purchased_tickets.txt");
    if (outFile.is_open()) 
    {
        for (const auto& ticket : purchasedTickets) 
        {
            outFile << "Date: " << ticket.getDate() << ", Train Number: " << ticket.getTrainNumber()
                << ", Carriage Number: " << ticket.getCarriageNumber() << ", Seat Number: " << ticket.getSeatNumber()
                << ", Passenger Name: " << ticket.getPassengerName() << ", Departure Station: " << ticket.getDepartureStation()
                << ", Arrival Station: " << ticket.getArrivalStation() << std::endl;
        }
        outFile.close();
        std::cout << "Purchased tickets have been written to purchased_tickets.txt" << std::endl;
    }
    else 
    {
        std::cerr << "Unable to open file for writing purchased tickets." << std::endl;
    }

    return 0;
}
