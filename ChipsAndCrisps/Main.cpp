#include <iostream>
#include <string>
#include <ctime>

#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"

int main() {
	Goods * g = new Goods(GoodsName::potatoes, 5);

	Vehicle *v = new Vehicle(VehicleType::crispsVehicle, "asdf", time(0));

	if (GoodsName::flavouring == GoodsName::flavouring)
	{
		std::cout << *v << std::endl;
	}


	return 0;
}