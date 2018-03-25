#pragma once

#include <ctime>
#include <string>
#include <ostream>
#include <cstdio>

#include "structures\heap_monitor.h"



struct VehicleType {
	std::string name;
	int capacity;
	int costsForRegion;

	bool operator== (const VehicleType& spec) const { return name == spec.name; }
};


class Vehicle
{
private:
	VehicleType type;
	std::string regNo;
	std::time_t recordDate;
	int totalCosts = 0;

public:
	static const VehicleType chipsType;
	static const VehicleType crispsType;

	Vehicle(VehicleType type, std::string regNo, std::time_t recordDate);
	~Vehicle();

	VehicleType getType() { return type; }
	std::time_t getRecordDate() { return recordDate; }

	void addCosts(size_t newCosts) { totalCosts += newCosts; }

	friend std::ostream& operator<<(std::ostream &strm, const Vehicle &obj);
	friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Vehicle &obj) {
	char date[30];
	sprintf(date, "%s", ctime(&obj.recordDate));
	return strm << obj.regNo << "  " << obj.type.name << "  " << obj.totalCosts << "  " << date;
}

