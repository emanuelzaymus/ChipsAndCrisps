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
