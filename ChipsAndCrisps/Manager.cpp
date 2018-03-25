#include "structures\heap_monitor.h"

#include <string>
#include <algorithm>
#include <iostream>

#include "Manager.h"
#include "Product.h"



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
			priorityPotatoesSups->push(g->getAveragePrice(), *supplier);
			break;
		case 2:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)oilSups, supplier);
			priorityOilSups->push(g->getAveragePrice(), *supplier);
			break;
		case 3:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)flavouringSups, supplier);
			priorityFlavouringSups->push(g->getAveragePrice(), *supplier);
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

void Manager::addByDate(structures::LinkedList<IRecordDateElem&> & list, IRecordDateElem & elem)
{
	int index = 0;
	std::time_t newDate = elem.getRecordDate();
	for (IRecordDateElem &e : list)
	{
		if (newDate - e.getRecordDate() < 0)
		{
			break;
		}
		index++;
	}
	list.insert(elem, index);
}

structures::LinkedList<Order&>* Manager::getOrders7Days()
{
	structures::LinkedList<Order&> *ret = new structures::LinkedList<Order&>();
	bool foundYet = false;
	time_t deathLine;
	for (Order &o : orders)
	{
		deathLine = o.getDeliveryDeathLine();
		if (today <= deathLine && (deathLine - today) / (24 * 60 * 60) < 7)
		{
			ret->add(o);
			foundYet = true;
		}
		else if (foundYet)
		{
			return ret;
		}
	}
	return ret;
}

void Manager::tryToBuyGoods(GoodsType type, double amount)
{
	structures::PriorityQueueUnsortedArrayList<Supplier&> *s;
	Goods *g;
	structures::PriorityQueueUnsortedArrayList<Supplier&> popped;

	if (type == Goods::potatoes) {
		s = priorityPotatoesSups;
		g = potatoes;
	}
	else if (type == Goods::oil) {
		s = priorityOilSups;
		g = oil;
	}
	else {
		s = priorityFlavouringSups;
		g = flavouring;
	}

	bool notBought = true;
	do
	{
		Supplier &sup = s->pop();
		if (sup.getGoods(type).getAmount() >= amount)
		{
			g->addAmount(sup.buy(type).getAmount());
			notBought = false;
		}
		popped.push(sup.getGoods(type).getRoundedAveragePrice(), sup);
	} while (!s->isEmpty() || notBought);

	while (!popped.isEmpty())
	{
		s->push(popped.peekPriority(), popped.pop());
	}
}

void Manager::cancelWorstOrders(double neededPotatoes, double neededOil, double neededFlavouring)
{
	// TODO
}

structures::LinkedList<Order&>* Manager::getDayOrders(time_t day0000)
{
	structures::LinkedList<Order&> *ret = new structures::LinkedList<Order&>();
	bool foundYet = false;
	time_t deathLine;
	for (Order &o : orders)
	{
		deathLine = o.getDeliveryDeathLine();
		if (day0000 <= deathLine && day0000 + 24 * 60 * 60 > deathLine)
		{
			ret->add(o);
			foundYet = true;
		}
		else if (foundYet)
		{
			return ret;
		}
	}
	return ret;
}

Manager::Manager(std::string companyName) : companyName(companyName)
{
	today = time(NULL);

	potatoes = new Goods(Goods::potatoes, 0);
	oil = new Goods(Goods::oil, 0);
	flavouring = new Goods(Goods::flavouring, 0);

	suppliers = new structures::LinkedList<Supplier*>();
	priorityPotatoesSups = new structures::PriorityQueueUnsortedArrayList<Supplier&>();
	priorityOilSups = new structures::PriorityQueueUnsortedArrayList<Supplier&>();
	priorityFlavouringSups = new structures::PriorityQueueUnsortedArrayList<Supplier&>();

	vehicles = new structures::LinkedList<Vehicle*>();
	customers = new structures::LinkedList<Customer*>();
}

Manager::~Manager()
{
	delete potatoes;
	delete oil;
	delete flavouring;

	while (!suppliers->isEmpty())
		delete suppliers->removeAt(0);
	delete suppliers;

	delete priorityPotatoesSups;
	delete priorityOilSups;
	delete priorityFlavouringSups;

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

void Manager::addOrder(Order & order)
{
	order.setRecordDate(time(NULL));
	if (order.getDeliveryDeathLine() - order.getRecordDate() < 7 * 24 * 60 * 60)
	{
		order.setAccepted(false);
		return;
	}
	structures::LinkedList<Order&> *thatDay = getDayOrders(order.getDeliveryDeathLine());
	double amountForDay = 0;
	ProductName name = order.getProduct().getName();
	for (Order &o : *thatDay)
	{
		if (o.getProduct().getName() == name)
		{
			amountForDay += o.getProduct().getAmount();
		}
	}
	delete thatDay;
	if (name == ProductName::chips && amountForDay + order.getProduct().getAmount() <= totalCapacityChips
		|| name == ProductName::crisps && amountForDay + order.getTotalPrice() <= totalCapacityCrisps)
	{
		orders.add(order);
	}
	else {
		order.setRejected();
		badOrders.add(order);
	}
}

void Manager::receiveOrders()
{
	for (Customer *c : *customers)
	{
		while (c->hasOrder())
		{
			addOrder(c->getOrder());
		}
	}
}

void Manager::checkOrders7days()
{
	double neededPotatoes(0);
	double neededOil(0);
	double neededFlavouring(0);

	structures::LinkedList<Order&> * orders7Days = getOrders7Days();
	for (Order &o : *orders7Days)
	{
		Product p = o.getProduct();
		if (p.getName() == ProductName::chips)
		{
			neededPotatoes += p.getAmount() * CHIPS_INGREDIENTS[0].getAmount();
			neededOil += p.getAmount() * CHIPS_INGREDIENTS[1].getAmount();
		}
		else {
			neededPotatoes += p.getAmount() * CRISPS_INGREDIENTS[0].getAmount();
			neededOil += p.getAmount() * CRISPS_INGREDIENTS[1].getAmount();
			neededFlavouring += p.getAmount() * CRISPS_INGREDIENTS[2].getAmount();
		}
	}
	delete orders7Days;

	if (potatoes->getAmount() < neededPotatoes)
		tryToBuyGoods(Goods::potatoes, neededPotatoes - potatoes->getAmount());

	if (oil->getAmount() < neededOil)
		tryToBuyGoods(Goods::oil, neededOil - oil->getAmount());

	if (flavouring->getAmount() < neededFlavouring)
		tryToBuyGoods(Goods::flavouring, neededFlavouring - flavouring->getAmount());

	if (potatoes->getAmount() < neededPotatoes || oil->getAmount() < neededOil || flavouring->getAmount() < neededFlavouring)
	{
		cancelWorstOrders(neededPotatoes, neededOil, neededFlavouring);
	}
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
