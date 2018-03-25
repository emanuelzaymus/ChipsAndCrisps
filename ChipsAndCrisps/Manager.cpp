#include "structures\heap_monitor.h"

#include <string>
#include <algorithm>

#include "Manager.h"



void Manager::addAlphabetical(structures::LinkedList<BusinessPartner*> &list, BusinessPartner *partner)
{
	int index = 0;
	std::string newName = partner->getName();
	std::transform(newName.begin(), newName.end(), newName.begin(), ::tolower);
	std::string existingName;
	for (BusinessPartner *s : list)
	{
		existingName = s->getName();
		std::transform(existingName.begin(), existingName.end(), existingName.begin(), ::tolower);
		if (newName.compare(existingName) <= 0)
		{
			break;
		}
		index++;
	}
	list.insert(partner, index);
}

void Manager::sortByGoods(Supplier * supplier)
{
	for (SupplierGoods *g : supplier->getGoods()) {
		switch (g->getType().code)
		{
		case 1:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)potatoesSups, supplier);
			priorityPotatoesSups.push(g->getAveragePrice(), *supplier);
			break;
		case 2:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)oilSups, supplier);
			priorityOilSups.push(g->getAveragePrice(), *supplier);
			break;
		case 3:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)flavouringSups, supplier);
			priorityFlavouringSups.push(g->getAveragePrice(), *supplier);
			break;
		}
	}
}

// IS NOT TESTED
void Manager::addByDate(Vehicle * vehicle)
{
	int index = 0;
	std::time_t newDate = vehicle->getRecordDate();
	for (Vehicle *v : *vehicles)
	{
		if (newDate - v->getRecordDate() < 0)
		{
			break;
		}
		index++;
	}
	vehicles->insert(vehicle, index);
}

Manager::Manager(std::string companyName) : companyName(companyName)
{
	suppliers = new structures::LinkedList<Supplier*>();
	vehicles = new structures::LinkedList<Vehicle*>();
	customers = new structures::LinkedList<Customer*>();
}

Manager::~Manager()
{
	while (!suppliers->isEmpty())
		delete suppliers->removeAt(0);
	delete suppliers;

	while (!vehicles->isEmpty())
		delete vehicles->removeAt(0);
	delete vehicles;

	while (!customers->isEmpty())
		delete customers->removeAt(0);
	delete customers;
}

void Manager::addSupplier(Supplier * supplier)
{
	addAlphabetical((structures::LinkedList<BusinessPartner*> &)*suppliers, supplier);
	sortByGoods(supplier);
}

void Manager::addVehicle(Vehicle * vehicle)
{
	addByDate(vehicle);
	if (vehicle->getType() == Vehicle::chipsType)
	{
		chipsVehicles.add(*vehicle);
		totalCapacityChips += vehicle->getType().capacity;
	}
	else {
		crispsVehicles.add(*vehicle);
		totalCapacityCrisps += vehicle->getType().capacity;
	}
}

void Manager::addCustomer(Customer * customer)
{
	addAlphabetical((structures::LinkedList<BusinessPartner*> &)*customers, customer);
}

structures::LinkedList<Supplier*>& Manager::getSuppliers(GoodsType type)
{
	switch (type.code)
	{
	case 1:
		return potatoesSups;
	case 2:
		return oilSups;
	case 3:
		return flavouringSups;
	}
}

//structures::PriorityQueueUnsortedArrayList<Supplier&> Manager::getPrioritySuppliers(GoodsType type)
//{
//	switch (type.code)
//	{
//	case 1:
//		return priorityPotatoesSups;
//	case 2:
//		return priorityOilSups;
//	case 3:
//		return priorityFlavouringSups;
//	}
//}

structures::LinkedList<Customer&> Manager::getCustomers(int region)
{// can by done in more effective way
	structures::LinkedList<Customer&> ret;
	for (Customer *c : *customers) {
		if (c->getAddress() == region)
		{
			ret.add(*c);
		}
	}
	return ret;
}
