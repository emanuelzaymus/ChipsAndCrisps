#include "structures\heap_monitor.h"

#include "Vehicle.h"



const VehicleType Vehicle::chipsType{ "Chips Vehicle ", 5000, 100 };
const VehicleType Vehicle::crispsType{ "Crisps Vehicle", 2000, 70 };


Vehicle::Vehicle(VehicleType type, std::string regNo, std::time_t recordDate)
	: type(type), regNo(regNo), recordDate(recordDate)
{
}

Vehicle::~Vehicle()
{
}

bool operator==(const Vehicle& lhs, const Vehicle& rhs)
{
	return lhs.recordDate == rhs.recordDate
		&& lhs.regNo == rhs.regNo
		&& lhs.type == rhs.type
		&& lhs.totalCosts == rhs.totalCosts;
}

