#pragma once
#include <string>
#include "Cinema.h"
#include "Date.h"
#include "Time.h"
class TicketOffice
{
	Cinema cinema;
public:
	TicketOffice(Cinema& cinema_);
	double buy_tickets(Date date, Time time, std::string name, unsigned hall_number, unsigned seat_type, unsigned count_of_tickets); // seat_type == 0 - base, 1 - vip
	void cancel_order(MovieSession& a, unsigned count);
};
