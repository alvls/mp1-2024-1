#include <iostream>
#include <locale.h>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

const int MAX_ROWS = 10;  // максимальное число рядов
const int SEATS_PER_ROW = 15;  // максимальное число мест в ряду

struct Seat {
	int row;
	int place;
	bool isReserved;
};

struct Showtime {
	std::string date;
	std::string time;
	std::vector<Seat> seats;
};

struct Hall {
	int hallNumber;
	float basePrice;
	std::vector<Showtime> showtimes;
};

class Cinema {
private:
	std::vector<Hall> halls;

public:
	Cinema() {
		halls.push_back({ 1, 10.0f, {} });
		halls.push_back({ 2, 15.0f, {} });
		generateSessions();
	}

	void generateSessions() {
		std::string times[] = { "10:00", "14:00", "22:00"};
		for (int day = 0; day < 30; ++day) {
			for (auto& hall : halls) {
				for (const std::string& time : times) {
					Showtime showtime;
					showtime.date = "2024-04-" + std::to_string(day + 1);
					showtime.time = time;
					for (int row = 1; row <= MAX_ROWS; ++row) {
						for (int place = 1; place <= SEATS_PER_ROW; ++place) {
							showtime.seats.push_back({ row, place, false });
						}
					}
					hall.showtimes.push_back(showtime);
				}
			}
		}
	}

	bool Cinema::checkAvailability(int hallNumber, const std::string& zoneType, int seatsRequired) {
		for (const auto& hall : halls) {
			if (hall.hallNumber == hallNumber) {
				for (const auto& showtime : hall.showtimes) {
					int availableSeats = 0;
					for (const Seat& seat : showtime.seats) {
						if (!seat.isReserved && inZone(seat.row, zoneType)) {
							availableSeats++;
						}
					}
					if (availableSeats >= seatsRequired) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool inZone(int row, const std::string& zoneType) {
		int threshold = MAX_ROWS / 2;
		if ((zoneType == "vip" && row <= threshold) || (zoneType == "обычная" && row > threshold)) {
			return true;
		}
		return false;
	}

	std::vector<Seat> reserveSeats(int hallNumber, const std::string& date, const std::string& time, const std::string& zoneType, int seatsRequired) {
		std::vector<Seat> reservedSeats;
		for (auto& hall : halls) {
			if (hall.hallNumber == hallNumber) {
				for (auto& showtime : hall.showtimes) {
					if (showtime.date == date && showtime.time == time) {
						for (Seat& seat : showtime.seats) {
							if (!seat.isReserved && inZone(seat.row, zoneType) && reservedSeats.size() < seatsRequired) {
								seat.isReserved = true;
								reservedSeats.push_back(seat);
							}
						}
					}
				}
			}
		}
		return reservedSeats;
	}
	
	void cancelSeatsReservation(int hallNumber, const std::vector<Seat>& seatsToCancel) {
		for (auto& hall : halls) {
			if (hall.hallNumber == hallNumber) {
				for (auto& showtime : hall.showtimes) {
					for (Seat& seat : showtime.seats) {
						for (const Seat& cancelSeat : seatsToCancel) {
							if (seat.row == cancelSeat.row && seat.place == cancelSeat.place && seat.isReserved) {
								seat.isReserved = false;
							}
						}
					}
				}
			}
		}
		std::cout << "Бронирование отменено для зала: " << hallNumber << std::endl;
	}

	float calculateTicketPrice(const std::string& movie, int hallNumber, const std::string& zoneType, int hour) {
		for (auto& hall : halls) {
			if (hall.hallNumber == hallNumber) {
				float basePrice = hall.basePrice;
				float zoneCoefficient = (zoneType == "vip") ? 2.0f : 1.0f;
				for (const auto& showtime : hall.showtimes) {
					if (hour < 12) {
						return basePrice * 0.75f * zoneCoefficient;
					}
					else if (hour >= 18) {
						return basePrice * 1.5f * zoneCoefficient;
					}
				}
				return basePrice * zoneCoefficient;
			}
		}
		return 0.0f;
	}
};



class TicketOffice {
private:
	Cinema& cinema;

public:
	TicketOffice(Cinema& theCinema) : cinema(theCinema) {}

	float processOrder(const std::string& date, const std::string& time, const std::string& movie, int hallNumber, const std::string& zoneType, int seatsRequired, const std::tm& currentTimeStruct) {
		if (!validateOrderTime(date, time, currentTimeStruct)) {
			return 0.0f;
		}

		if (!cinema.checkAvailability(hallNumber, zoneType, seatsRequired)) {
			std::cout << "Недостаточно доступных мест в запрашиваемой зоне." << std::endl;
			return 0.0f;
		}
		else
			std::cout << "Есть свободные места." << std::endl;

		std::vector<Seat> reservedSeats = cinema.reserveSeats(hallNumber, date, time, zoneType, seatsRequired);
		if (reservedSeats.size() < seatsRequired) {
			std::cout << "Недостаточно мест было успешно зарезервировано." << std::endl;
			return 0.0f;
		}

		int hour = std::stoi(time.substr(0, 2));
		float pricePerTicket = cinema.calculateTicketPrice(movie, hallNumber, zoneType, hour);
		float totalPrice = pricePerTicket * static_cast<int>(reservedSeats.size());

		issueTickets(date, time, movie, hallNumber, reservedSeats);

		return totalPrice;
	}

	void cancelOrder(int hallNumber, const std::vector<Seat>& seats) {
		cinema.cancelSeatsReservation(hallNumber, seats);
	}

	bool validateOrderTime(const std::string& date, const std::string& time, const std::tm& currentTimeStruct) {
		std::tm orderTime = {};
		std::istringstream dateStream(date + " " + time);
		dateStream >> std::get_time(&orderTime, "%Y-%m-%d %H:%M");
		if (dateStream.fail()) {
			std::cerr << "Ошибка в формате даты или времени" << std::endl;
			return false;
		}

		std::time_t orderTimeEpoch = std::mktime(&orderTime);
		std::time_t currentTime = std::mktime(const_cast<std::tm*>(&currentTimeStruct));

		double secondsDiff = difftime(orderTimeEpoch, currentTime);
		int daysDiff = static_cast<int>(secondsDiff / (60 * 60 * 24));

		if (daysDiff < 0 || daysDiff > 3) {
			std::cout << "Билеты можно заказывать только за 3 дня до события и не ранее." << std::endl;
			return false;
		}

		if (daysDiff == 0) {
			std::tm tenMinutesAfterStart = orderTime;
			tenMinutesAfterStart.tm_min += 10;
			std::time_t tenMinutesAfterStartEpoch = std::mktime(&tenMinutesAfterStart);
			if (currentTime > tenMinutesAfterStartEpoch) {
				std::cout << "Невозможно обработать заказ. Заказы на сеанс закрываются через 10 минут после его начала." << std::endl;
				return false;
			}
		}

		return true;
	}

	void issueTickets(const std::string& date, const std::string& time, const std::string& movie, int hallNumber, const std::vector<Seat>& reservedSeats) {
		for (const Seat& seat : reservedSeats) {
			std::cout << "Билет: Дата: " << date << ", Время: " << time << ", Фильм: " << movie
				<< ", Зал: " << hallNumber << ", Ряд: " << seat.row << ", Место: " << seat.place << std::endl;
		}
	}
};




int main() {
	setlocale(LC_ALL, "rus");
	Cinema cinema;
	TicketOffice ticketOffice(cinema);

	std::tm currentTimeStruct = {};

	// Задание времени текущему моменту
	int year = 2024;
	int month = 4;
	currentTimeStruct.tm_year = year - 1900;
	currentTimeStruct.tm_mon = month - 1;  
	currentTimeStruct.tm_mday = 10;
	currentTimeStruct.tm_hour = 9;
	currentTimeStruct.tm_min = 55;

	std::string date = "2024-04-10";
	std::string time = "10:00";
	std::string movie = "Avengers";
	int hallNumber = 2;
	std::string zoneType = "обычная";
	int seatsRequired = 5;

	// Попытка зарезервировать билеты на сеанс
	std::cout << "Попытка зарезервировать " << seatsRequired << " билетов на сеанс " << std::endl;
	float totalCost = ticketOffice.processOrder(date, time, movie, hallNumber, zoneType, seatsRequired, currentTimeStruct);
	if (totalCost > 0) {
		std::cout << "Общая стоимость заказа: " << totalCost << " рублей." << std::endl;
	}
	else {
		std::cout << "Не удалось зарезервировать места." << std::endl;
	}

	std::cout << "" << std::endl;

	// Отмена билетов, если заказ был успешно выполнен
	if (totalCost > 0) {
		std::cout << "Отмена заказа..." << std::endl;
		std::vector<Seat> reservedSeats = cinema.reserveSeats(hallNumber, date, time, zoneType, seatsRequired);
		ticketOffice.cancelOrder(hallNumber, reservedSeats);
	}

	std::cout << "" << std::endl;

	year = 2024;
	month = 4;
	currentTimeStruct.tm_year = year - 1900;
	currentTimeStruct.tm_mon = month - 1;
	currentTimeStruct.tm_mday = 10;
	currentTimeStruct.tm_hour = 22;
	currentTimeStruct.tm_min = 10; 

	date = "2024-04-10";
	time = "22:00";
	movie = "Titanic";
	hallNumber = 1;
	zoneType = "vip";
	seatsRequired = 2;

	// Попытка зарезервировать билеты с поздним временем
	std::cout << "Попытка зарезервировать " << seatsRequired << " билетов на сеанс " << std::endl;
	totalCost = ticketOffice.processOrder(date, time, movie, hallNumber, zoneType, seatsRequired, currentTimeStruct);
	if (totalCost > 0) {
		std::cout << "Общая стоимость заказа: " << totalCost << " рублей." << std::endl;
	}
	else {
		std::cout << "Не удалось зарезервировать места." << std::endl;
	}

	std::cin.get();
	return 0;

}
