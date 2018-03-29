#pragma once

#include <ctime>
#include <string>
#include <ostream>
#include <cstdio>

#include "structures\heap_monitor.h"
#include "structures\stack\explicit_stack.h"

#include "IRecordDateElem.h"
#include "Order.h"


struct VehicleType {
	std::string name;
	int capacity;
	int costsForRegion;

	bool operator== (const VehicleType& spec) const { return name == spec.name; }
};


class Vehicle :IRecordDateElem
{
private:
	VehicleType type;
	std::string regNo;
	std::time_t recordDate;
	int totalCosts = 0;
	structures::ExplicitStack<Order&> orders;
	int amount = 0;

public:
	static const VehicleType chipsType;
	static const VehicleType crispsType;

	Vehicle(VehicleType type, std::string regNo, std::time_t recordDate);
	~Vehicle();

	VehicleType getType() { return type; }
	std::time_t getRecordDate() { return recordDate; }
	bool addOrder(Order& o);
	int getFreeSpace() { return type.capacity - amount; }
	bool isFull() { return type.capacity == amount; }
	structures::ExplicitStack<Order&> getOrders() { return orders; }

	void addCosts(size_t newCosts) { totalCosts += newCosts; }

	friend std::ostream& operator<<(std::ostream &strm, const Vehicle &obj);
	friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Vehicle &obj) {
	char date[30];
	sprintf(date, "%s", ctime(&obj.recordDate));
	return strm << obj.regNo << "  " << obj.type.name << "  " << obj.totalCosts << "  " << date;
}

