#include "structures\heap_monitor.h"

#include "Vehicle.h"



const Specification chipsSpec{ "Chips Vehicle", 5, 100 };
const Specification crispsSpec{ "Crisps Vehicle", 2, 70 };


Vehicle::Vehicle(VehicleType type, std::string regNo, std::time_t recordDate)
	: regNo(regNo), recordDate(recordDate)
{
	if (type == VehicleType::chipsVehicle)
		spec = chipsSpec;
	else
		spec = crispsSpec;

}

Vehicle::~Vehicle()
{
}


bool operator==(const Vehicle& lhs, const Vehicle& rhs)
{
	return lhs.recordDate == rhs.recordDate 
		&& lhs.regNo == rhs.regNo 
		&& lhs.spec == rhs.spec
		&& lhs.totalCosts == rhs.totalCosts;
}