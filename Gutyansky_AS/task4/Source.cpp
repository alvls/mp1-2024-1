#include <iostream>
#include "Pedometer.hpp"

void PrintPedometerInfo(const Pedometer& p) {
	std::cout << p.GetRecord(0);
	std::cout << "Average steps: " << p.GetAverageStepCount() << std::endl;
	std::cout << "Average steps March 2023: " << p.GetAverageStepCountMonth(3, 2023) << std::endl;
	std::cout << "Average steps March 2024: " << p.GetAverageStepCountMonth(3, 2024) << std::endl;
	std::cout << "Average steps April 2024: " << p.GetAverageStepCountMonth(4, 2024) << std::endl;
	std::cout << "Average steps Monday: " << p.GetAverageWeekdaySteps(1) << std::endl;
	std::cout << "Average steps Thursday: " << p.GetAverageWeekdaySteps(4) << std::endl;
	std::cout << "Average steps Saturday: " << p.GetAverageWeekdaySteps(6) << std::endl;
	Pedometer::MaxStepsResponse maxSteps = p.GetMaximumSteps();
	std::cout << "Max Steps: " << maxSteps.Steps << std::endl;
	std::cout << "Date: " << maxSteps.Day << "." << maxSteps.Month << "." << maxSteps.Year << std::endl;
	Pedometer::MaxStepsResponse maxSteps2 = p.GetMaximumSteps(4, 2024);
	std::cout << "Max Steps April 2024: " << maxSteps2.Steps << std::endl;
	std::cout << "Date: " << maxSteps2.Day << "." << maxSteps2.Month << "." << maxSteps2.Year << std::endl;
}

int main() { 
	Pedometer test;
	test.AddRecord(16, 3, 2024, 8, 30, 12, 00, 3578);
	test.AddRecord(16, 3, 2024, 14, 45, 18, 59, 11294);
	test.AddRecord(14, 3, 2024, 8, 00, 19, 45, 10679);
	test.AddRecord(19, 4, 2024, 13, 21, 16, 30, 10000);
	std::cout << "Pedometer 1:\n";
	PrintPedometerInfo(test);
	test.SaveFile("results.txt");

	Pedometer test2;
	test2.LoadFile("results.txt");
	std::cout << "\nPedometer 2, results must be the same:\n";
	PrintPedometerInfo(test2);
	
  return 0;
}