#pragma once

#include <ctime>
#include <string>
#include <ostream>


struct Specification {
	std::string name;
	int capacity;
	int costsForRegion;
};

enum VehicleType { chipsVehicle, crispsVehicle };


class Vehicle
{
private:
	Specification spec;
	std::string regNo;
	std::time_t recordDate;
	int totalCosts = 0;

public:
	Vehicle(VehicleType type, std::string regNo, std::time_t recordDate);
	~Vehicle();

	void addCosts(size_t newCosts) { totalCosts += newCosts; }

	friend std::ostream& operator<<(std::ostream &strm, const Vehicle &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const Vehicle &obj) {
	return strm << obj.spec.name << "  " << obj.spec.capacity;
}