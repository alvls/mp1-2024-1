#include "GZD.h"

bool GorkyRailway::checkAvailability(int trainNumber, SeatType seatType, int numTickets)
{
    // Check if the train exists
    if (tickets.find(trainNumber) == tickets.end())
    {
        return false; // Train does not exist
    }

    // Count available seats of the given seat type
    int availableSeats = 0;
    for (const auto& ticket : tickets[trainNumber])
    {
        if (ticket.getSeatType() == seatType)
        {
            availableSeats++;
        }
    }

    // Check if enough seats are available
    return availableSeats >= numTickets;
}

bool GorkyRailway::reserveSeats(int trainNumber, SeatType seatType, int numTickets)
{
    // Check if the train exists
    if (tickets.find(trainNumber) == tickets.end())
    {
        return false; // Train does not exist
    }

    // Reserve seats
    int seatsReserved = 0;
    for (auto& ticket : tickets[trainNumber])
    {
        if (seatsReserved >= numTickets)
        {
            break; // All tickets reserved
        }
        if (ticket.getSeatType() == seatType && !ticket.isReserved())
        {
            ticket.setReserved(true);
            seatsReserved++;
        }
    }

    // Check if all requested tickets were reserved
    return seatsReserved == numTickets;
}

double GorkyRailway::calculateTotalCost(int trainNumber, TrainType trainType, SeatType seatType, int numTickets)
{
    if (tickets.find(trainNumber) == tickets.end())
    {
        return -1.0;
    }
    double ticketPrice = 0.0;
    for (const auto& ticket : tickets[trainNumber]) {
        if (ticket.getTrainType() == trainType && ticket.getSeatType() == seatType)
        {
            ticketPrice += ticket.calculateTicketPrice();
            numTickets--;
            if (numTickets == 0)
            {
                break;
            }
        }
    }
    return ticketPrice;
}

bool GorkyRailway::cancelTicketOrder(int trainNumber, SeatType seatType, int numTickets)
{
    if (tickets.find(trainNumber) == tickets.end())
    {
        return false;
    }
    int seatsCancelled = 0;
    for (auto& ticket : tickets[trainNumber]) {
        if (seatsCancelled >= numTickets) {
            break;
        }
        if (ticket.getSeatType() == seatType && ticket.isReserved()) {
            ticket.setReserved(false);
            seatsCancelled++;
        }
    }
    return seatsCancelled == numTickets;
}

void GorkyRailway::generateTicketsToFile(const std::string& filename)
{
    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& trainPair : tickets)
    {
        int trainNumber = trainPair.first;
        const auto& trainTickets = trainPair.second;

        for (const auto& ticket : trainTickets)
        {
            if (ticket.isReserved())
            {
                outputFile << "Date: " << ticket.getDate() << ", Train Number: " << ticket.getTrainNumber()
                    << ", Carriage Number: " << ticket.getCarriageNumber() << ", Seat Number: " << ticket.getSeatNumber()
                    << ", Passenger Name: " << ticket.getPassengerName() << ", Departure Station: " << ticket.getDepartureStation()
                    << ", Arrival Station: " << ticket.getArrivalStation() << std::endl;
            }
        }
    }

    outputFile.close();
}

std::vector<Ticket> GorkyRailway::getReservedTickets(int trainNumber, SeatType seatType, int numTickets)
{
    std::vector<Ticket> reservedTickets;
    for (const auto& ticket : tickets[trainNumber])
    {
        if (ticket.getSeatType() == seatType && ticket.isReserved())
        {
            reservedTickets.push_back(ticket);
            if (reservedTickets.size() == numTickets)
            {
                break;
            }
        }
    }
    return reservedTickets;
}

void GorkyRailway::generateLastochkaTickets(int numTrainsPerDay, int numCarsPerTrain, int numSeatsPerCar) {
    for (int i = 1; i <= numTrainsPerDay; ++i) {
        for (int j = 1; j <= numCarsPerTrain; ++j) {
            for (int k = 1; k <= numSeatsPerCar; ++k) {
                std::string passengerName = "Passenger " + std::to_string(i) + "-" + std::to_string(j) + "-" + std::to_string(k);
                time_t now = time(0);
                tm future = *localtime(&now);
                future.tm_mday += rand() % 30; // Add random number of days (up to 30)
                std::string date = std::to_string(future.tm_year + 1900) + "-" + std::to_string(future.tm_mon + 1) + "-" + std::to_string(future.tm_mday);
                int trainNumber = getRandomInt(1, 100);
                int carriageNumber = (i - 1) * numCarsPerTrain + j;
                int seatNumber = (j - 1) * numSeatsPerCar + k;

                tickets[trainNumber].emplace_back(date, trainNumber, carriageNumber, seatNumber, SeatType::SITTING, TrainType::LASTOCHKA,
                    passengerName, "Nizhny Novgorod", "Moscow");
            }
        }
    }
}

void GorkyRailway::generateBrandedTickets(int numTrainsPerDay, int numSVCars, int numCompartmentCars, int numReservedCars,
    int numSeatsPerSV, int numSeatsPerCompartment, int numSeatsPerReserved) {
    for (int i = 1; i <= numTrainsPerDay; ++i) {
        for (int j = 1; j <= numSVCars; ++j) {
            for (int k = 1; k <= numSeatsPerSV; ++k) {
                std::string passengerName = "Passenger " + std::to_string(i) + "-" + std::to_string(j) + "-" + std::to_string(k);
                time_t now = time(0);
                tm future = *localtime(&now);
                future.tm_mday += rand() % 30; // Add random number of days (up to 30)
                std::string date = std::to_string(future.tm_year + 1900) + "-" + std::to_string(future.tm_mon + 1) + "-" + std::to_string(future.tm_mday);
                int trainNumber = getRandomInt(1, 100);
                int carriageNumber = (i - 1) * (numSVCars + numCompartmentCars + numReservedCars) + j;
                int seatNumber = (j - 1) * numSeatsPerSV + k;

                tickets[trainNumber].emplace_back(date, trainNumber, carriageNumber, seatNumber, SeatType::SV, TrainType::BRANDED,
                    passengerName, "Nizhny Novgorod", "Moscow");
            }
        }

        for (int j = numSVCars + 1; j <= numSVCars + numCompartmentCars; ++j) {
            for (int k = 1; k <= numSeatsPerCompartment; ++k) {
                std::string passengerName = "Passenger " + std::to_string(i) + "-" + std::to_string(j) + "-" + std::to_string(k);
                time_t now = time(0);
                tm future = *localtime(&now);
                future.tm_mday += rand() % 30; // Add random number of days (up to 30)
                std::string date = std::to_string(future.tm_year + 1900) + "-" + std::to_string(future.tm_mon + 1) + "-" + std::to_string(future.tm_mday);
                int trainNumber = getRandomInt(1, 100);
                int carriageNumber = (i - 1) * (numSVCars + numCompartmentCars + numReservedCars) + j;
                int seatNumber = (j - numSVCars - 1) * numSeatsPerCompartment + k;

                tickets[trainNumber].emplace_back(date, trainNumber, carriageNumber, seatNumber, SeatType::COMPARTMENT, TrainType::BRANDED,
                    passengerName, "Nizhny Novgorod", "Moscow");
            }
        }

        for (int j = numSVCars + numCompartmentCars + 1; j <= numSVCars + numCompartmentCars + numReservedCars; ++j) {
            for (int k = 1; k <= numSeatsPerReserved; ++k) {
                std::string passengerName = "Passenger " + std::to_string(i) + "-" + std::to_string(j) + "-" + std::to_string(k);
                time_t now = time(0);
                tm future = *localtime(&now);
                future.tm_mday += rand() % 30; // Add random number of days (up to 30)
                std::string date = std::to_string(future.tm_year + 1900) + "-" + std::to_string(future.tm_mon + 1) + "-" + std::to_string(future.tm_mday);
                int trainNumber = getRandomInt(1, 100);
                int carriageNumber = (i - 1) * (numSVCars + numCompartmentCars + numReservedCars) + j;
                int seatNumber = (j - numSVCars - numCompartmentCars - 1) * numSeatsPerReserved + k;

                tickets[trainNumber].emplace_back(date, trainNumber, carriageNumber, seatNumber, SeatType::SLEEPING, TrainType::BRANDED,
                    passengerName, "Nizhny Novgorod", "Moscow");
            }
        }
    }
}

void GorkyRailway::generateExpressTickets(int numTrainsPerDay, int numCarsPerTrain, int numSeatsPerCar) {
    for (int i = 1; i <= numTrainsPerDay; ++i) {
        for (int j = 1; j <= numCarsPerTrain; ++j) {
            for (int k = 1; k <= numSeatsPerCar; ++k) {
                std::string passengerName = "Passenger " + std::to_string(i) + "-" + std::to_string(j) + "-" + std::to_string(k);
                time_t now = time(0);
                tm future = *localtime(&now);
                future.tm_mday += rand() % 30; // Add random number of days (up to 30)
                std::string date = std::to_string(future.tm_year + 1900) + "-" + std::to_string(future.tm_mon + 1) + "-" + std::to_string(future.tm_mday);
                int trainNumber = getRandomInt(1, 100);
                int carriageNumber = (i - 1) * numCarsPerTrain + j;
                int seatNumber = (j - 1) * numSeatsPerCar + k;

                tickets[trainNumber].emplace_back(date, trainNumber, carriageNumber, seatNumber, SeatType::SITTING, TrainType::EXPRESS,
                    passengerName, "Nizhny Novgorod", "Moscow");
            }
        }
    }
}

int GorkyRailway::getRandomInt(int min, int max)
{
    return min + (rand() % (max - min + 1));
}
