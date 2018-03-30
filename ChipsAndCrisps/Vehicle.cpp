#include "structures\heap_monitor.h"

#include "Vehicle.h"



const VehicleType Vehicle::chipsType{ "Chips Vehicle ", 5000, 100 };
const VehicleType Vehicle::crispsType{ "Crisps Vehicle", 2000, 70 };


void Vehicle::addRegion(Order & ord)
{
	for each (int region in inRegions)
	{
		if (region == ord.getAddress())
			return;
	}
	inRegions.add(ord.getAddress());
}

Vehicle::Vehicle(VehicleType type, std::string regNo, std::time_t recordDate)
	: type(type), regNo(regNo), recordDate(recordDate)
{
}

Vehicle::~Vehicle()
{
}

bool Vehicle::addOrder(Order & ord)
{
	if (amount < type.capacity)
	{
		orders.push(ord);
		amount += ord.getProduct().getAmount();
		addRegion(ord);
		return true;
	}
	return false;
}

void Vehicle::deliveryMade()
{
	orders.clear();
	amount = 0;
	totalCosts += inRegions.size() * type.costsForRegion;
	inRegions.clear();
}

bool operator==(const Vehicle& lhs, const Vehicle& rhs)
{
	return lhs.recordDate == rhs.recordDate
		&& lhs.regNo == rhs.regNo
		&& lhs.type == rhs.type
		&& lhs.totalCosts == rhs.totalCosts;
}

