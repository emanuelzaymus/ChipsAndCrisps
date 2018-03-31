#pragma once

#include <ctime>
#include <string>
#include <ostream>
#include <cstdio>

#include "structures\heap_monitor.h"
#include "structures\stack\explicit_stack.h"

#include "IRecordDateElem.h"
#include "Order.h"

class Order;

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
	structures::ArrayList<int> inRegions;

	void addRegion(Order& ord);

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

	double deliveryMade();

	friend std::ostream& operator<<(std::ostream &strm, const Vehicle &obj);
	friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Vehicle &obj) {
	char date[30];
	sprintf(date, "%s", ctime(&obj.recordDate));
	char costs[30];
	sprintf(costs, "%4d", obj.totalCosts);
	return strm << obj.regNo << "  " << obj.type.name << "  " << costs << " EUR  " << date;
}

