#pragma once

#include <ctime>
#include <string>
#include <ostream>

#include "structures\heap_monitor.h"


struct Specification {
	std::string name;
	int capacity;
	int costsForRegion;

	bool operator== (const Specification& spec) const { return name == spec.name; }
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
	friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Vehicle &obj) {
	return strm << obj.spec.name << "  " << obj.spec.capacity;
}

