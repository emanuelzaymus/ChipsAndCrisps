#include "structures\heap_monitor.h"

#include <string>
#include <algorithm>
#include <iostream>

#include "Manager.h"
#include "Product.h"
#include "Customer.h"
#include "Order.h"
#include "Vehicle.h"


time_t Manager::TODAY = time(NULL);

void Manager::addAlphabetical(structures::LinkedList<BusinessPartner*> &list, BusinessPartner *partner)
{
	int index = 0;
	std::string newName = partner->getName();
	std::transform(newName.begin(), newName.end(), newName.begin(), ::tolower);
	std::string existingName;
	for (BusinessPartner *bp : list)
	{
		existingName = bp->getName();
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
			priorityPotatoesSups->push(g->getAveragePrice30(), *supplier);
			break;
		case 2:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)oilSups, supplier);
			priorityOilSups->push(g->getAveragePrice30(), *supplier);
			break;
		case 3:
			addAlphabetical((structures::LinkedList<BusinessPartner*> &)flavouringSups, supplier);
			priorityFlavouringSups->push(g->getAveragePrice30(), *supplier);
			break;
		}
	}
}

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

structures::ArrayList<double> Manager::getNeedsFor(time_t fromDay, time_t toDay)
{
	structures::ArrayList<double> needs;
	double neededPotatoes(0);
	double neededOil(0);
	double neededFlavouring(0);

	structures::LinkedList<Order&> * ordersFromTo = getOrdersBetweenDays(orders, fromDay, toDay);
	for (Order &o : *ordersFromTo)
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
	delete ordersFromTo;

	needs.add(neededPotatoes);
	needs.add(neededOil);
	needs.add(neededFlavouring);

	return needs;
}

void Manager::tryToBuyGoods(GoodsType type, double amount)
{
	structures::Heap<Supplier&> *sups;
	Goods *tg;
	structures::Heap<Supplier&> popped;

	if (type == Goods::potatoes) {
		sups = priorityPotatoesSups;
		tg = tomorrowsPotatoes;
	}
	else if (type == Goods::oil) {
		sups = priorityOilSups;
		tg = tomorrowsOil;
	}
	else {
		sups = priorityFlavouringSups;
		tg = tomorrowsFlavouring;
	}

	while (!sups->isEmpty() && amount > 0)
	{
		Supplier &sup = sups->pop();
		amount -= sup.getGoods(type).getAmount();
		costs += sup.getGoods(type).getTotalPrice();
		tg->addAmount(sup.buy(type).getAmount());

		popped.push(sup.getGoods(type).getRoundedAveragePrice30(), sup);
	}

	int peekedPriority;
	while (!popped.isEmpty())
	{
		peekedPriority = popped.peekPriority();
		sups->push(peekedPriority, popped.pop());
	}
}

void Manager::checkTomorrowsOrders()
{
	structures::ArrayList<double> tommorrowsNeeds = getNeedsFor(TODAY + DAY_SEC, TODAY + DAY_SEC);

	if (tommorrowsNeeds[0] > potatoes->getAmount() + tomorrowsPotatoes->getAmount()) {
		cancelOrders(Goods::potatoes, tommorrowsNeeds[0] - potatoes->getAmount() - tomorrowsPotatoes->getAmount());
		tommorrowsNeeds = getNeedsFor(TODAY + DAY_SEC, TODAY + DAY_SEC);
	}

	if (tommorrowsNeeds[1] > oil->getAmount() + tomorrowsOil->getAmount()) {
		cancelOrders(Goods::oil, tommorrowsNeeds[1] - oil->getAmount() - tomorrowsOil->getAmount());
		tommorrowsNeeds = getNeedsFor(TODAY + DAY_SEC, TODAY + DAY_SEC);
	}

	if (tommorrowsNeeds[2] > flavouring->getAmount() + tomorrowsFlavouring->getAmount())
		cancelOrders(Goods::flavouring, tommorrowsNeeds[2] - flavouring->getAmount() - tomorrowsFlavouring->getAmount());
}

void Manager::produceTomorrowsProducts()
{
	int producedChips(0);
	int producedCrisps(0);

	int minRegionChips(0);
	int minRegionCrisps(0);
	structures::LinkedList<Order&> *tomorrowsOrders = getOrdersBetweenDays(orders, TODAY + DAY_SEC, TODAY + DAY_SEC);
	for (Order& ord : *tomorrowsOrders)
	{
		if (ord.getProduct().getName() == ProductName::chips) {
			producedChips += ord.getProduct().getAmount();

			potatoes->addAmount(-ord.getProduct().getAmount() * CHIPS_INGREDIENTS[0].getAmount());
			oil->addAmount(-ord.getProduct().getAmount() * CHIPS_INGREDIENTS[1].getAmount());

			producedOrdersChips.push(-ord.getAddress(), ord);
			if (minRegionChips > ord.getAddress())
				minRegionChips = ord.getAddress();
		}
		else {
			producedCrisps += ord.getProduct().getAmount();
			producedOrdersCrisps.push(-ord.getAddress(), ord);

			potatoes->addAmount(-ord.getProduct().getAmount() * CRISPS_INGREDIENTS[0].getAmount());
			oil->addAmount(-ord.getProduct().getAmount() * CRISPS_INGREDIENTS[1].getAmount());
			flavouring->addAmount(-ord.getProduct().getAmount() * CRISPS_INGREDIENTS[2].getAmount());

			if (minRegionCrisps > ord.getAddress())
				minRegionCrisps = ord.getAddress();
		}
		orders.tryRemove(ord);
	}
	delete tomorrowsOrders;

	structures::LinkedList<Order&> * extraChips = getOrdersBySpec(ProductName::chips, totalCapacityChips - producedChips, minRegionChips);
	structures::LinkedList<Order&> * extraCrisps = getOrdersBySpec(ProductName::crisps, totalCapacityCrisps - producedCrisps, minRegionCrisps);

	for (Order& ord : *extraChips) {
		extraProducedOrdersChips.push(-ord.getAddress(), ord);
		orders.tryRemove(ord);
	}
	for (Order& ord : *extraCrisps) {
		extraProducedOrdersCrisps.push(-ord.getAddress(), ord);
		orders.tryRemove(ord);
	}

	delete extraChips;
	delete extraCrisps;
}

void Manager::loadVehicles()
{
	loadWithOrders(chipsVehicles, producedOrdersChips);
	loadWithOrders(crispsVehicles, producedOrdersCrisps);

	loadWithOrders(chipsVehicles, extraProducedOrdersChips);
	loadWithOrders(crispsVehicles, extraProducedOrdersCrisps);
}

void Manager::ordersDelivered()
{
	while (!sentOrders.isEmpty())
	{
		Order& ord = sentOrders.removeAt(0);
		ord.makeDone();
		goodOrders.add(ord);
		income += ord.getTotalPrice();
	}
	for each (Vehicle *vehicle in *vehicles)
	{
		costs += vehicle->deliveryMade();
	}
}

Supplier & Manager::getBestSupplier(GoodsType type)
{
	structures::LinkedList<Supplier*> *sups = &potatoesSups;
	switch (type.code) {
	case 1:
		sups = &potatoesSups;
		break;
	case 2:
		sups = &oilSups;
		break;
	case 3:
		sups = &flavouringSups;
		break;
	}
	if (sups->isEmpty())
	{
		throw std::exception("Empty LinkedList<Supplier*> * !");
	}
	Supplier* bestSupplier = (*sups)[0];
	int bestBoughtAmount = bestSupplier->getGoods(type).getBoughtAmount30();
	for each (Supplier *sup in *sups)
	{
		if (sup->getGoods(type).getBoughtAmount30() > bestBoughtAmount) {
			bestSupplier = sup;
			bestBoughtAmount = bestSupplier->getGoods(type).getBoughtAmount30();
		}
	}
	return *bestSupplier;
}

void Manager::loadWithOrders(structures::LinkedList<Vehicle&> &vehiclesToLoad, structures::Heap<Order&> &ordersToLoad)
{
	for (Vehicle &vehicle : vehiclesToLoad)
	{
		if (vehicle.isFull())
			continue;
		if (ordersToLoad.isEmpty())
			break;
		while (!ordersToLoad.isEmpty())
		{
			Order& ord = ordersToLoad.peek();
			if (!vehicle.isFull())
			{
				if (vehicle.getFreeSpace() < ord.getProduct().getAmount())
				{
					Order& splitted = ord.split(vehicle.getFreeSpace());
					ordersToLoad.push(-splitted.getAddress(), splitted);
				}
				vehicle.addOrder(ord);
				sentOrders.add(ord);
				ordersToLoad.pop();
			}
			else {
				break;
			}
		}
	}
}

void Manager::cancelOrders(Goods type, double howMuch)
{
	double cancelledAmount = 0;
	structures::LinkedList<Order&> *tomorrows = getOrdersBetweenDays(orders, TODAY + DAY_SEC, TODAY + DAY_SEC);
	structures::Heap<Order&> smallestProfitTomorrow;

	int length = tomorrows->size();
	for (size_t i = 0; i < length; i++)
	{
		Order& ord = tomorrows->removeAt(0);
		smallestProfitTomorrow.push((int)ord.getTotalPrice(), ord);
	}
	delete tomorrows;

	while (!smallestProfitTomorrow.isEmpty() && cancelledAmount < howMuch)
	{
		Order& ord = smallestProfitTomorrow.pop();
		if (!(type == Goods::flavouring && ord.getProduct().getName() != ProductName::crisps))
		{
			ord.cancel();
			badOrders.add(ord);
			cancelledAmount += ord.getProduct().getAmount();
			orders.tryRemove(ord);
		}
	}
}

//Have to delete object it returns! 
structures::LinkedList<Order&>* Manager::getOrdersBySpec(ProductName name, int howMuch, int region)
{
	int amount(0);
	structures::LinkedList<Order&> *ret = new structures::LinkedList<Order&>();
	structures::LinkedList<Order&> *extraOrders = getOrdersBetweenDays(orders, TODAY + 2 * DAY_SEC, TODAY + 100 * DAY_SEC);
	for (Order &ord : *extraOrders)
	{
		if (ord.getProduct().getName() == name && ord.getAddress() == region)
		{
			if (amount + ord.getProduct().getAmount() > howMuch)
			{
				Order& splitted = ord.split(howMuch - amount);
				addByDate((structures::LinkedList<IRecordDateElem&> &)orders, (IRecordDateElem&)ord);
			}
			amount += ord.getProduct().getAmount();
			ret->add(ord);
			if (amount >= howMuch)
				break;
		}
	}
	delete extraOrders;
	return ret;
}

//Have to delete object it returns! 
structures::LinkedList<Order&>* Manager::getOrdersBetweenDays(structures::LinkedList<Order&> &ords, time_t fromDay, time_t toDay)
{
	struct tm * dayInfo;
	dayInfo = localtime(&fromDay);
	int from_year = dayInfo->tm_year;
	int from_yday = dayInfo->tm_yday;
	dayInfo = localtime(&toDay);
	int to_year = dayInfo->tm_year;
	int to_yday = dayInfo->tm_yday;

	structures::LinkedList<Order&> *ret = new structures::LinkedList<Order&>();
	time_t checkedDate;
	for (Order &o : ords)
	{
		if (o.isDone())
			checkedDate = o.getDeliveryDate();
		else if (o.isRejected() || o.isCancelled())
			checkedDate = o.getRecordDate();
		else
			checkedDate = o.getDeliveryDeathLine();

		dayInfo = localtime(&checkedDate);
		int y = dayInfo->tm_year;
		int d = dayInfo->tm_yday;
		if (from_year == y && to_year == y && from_yday <= d &&to_yday >= d
			|| from_year < y && to_year == y &&to_yday >= d
			|| from_year == y && to_year > y && from_yday <= d
			|| from_year < y && to_year > y)
		{
			ret->add(o);
		}
	}
	return ret;
}

Manager::Manager(std::string companyName) : companyName(companyName)
{
	potatoes = new Goods(Goods::potatoes, 0);
	oil = new Goods(Goods::oil, 0);
	flavouring = new Goods(Goods::flavouring, 0);

	tomorrowsPotatoes = new Goods(Goods::potatoes, 0);
	tomorrowsOil = new Goods(Goods::oil, 0);
	tomorrowsFlavouring = new Goods(Goods::flavouring, 0);

	suppliers = new structures::LinkedList<Supplier*>();
	priorityPotatoesSups = new structures::Heap<Supplier&>();
	priorityOilSups = new structures::Heap<Supplier&>();
	priorityFlavouringSups = new structures::Heap<Supplier&>();

	vehicles = new structures::LinkedList<Vehicle*>();
	customers = new structures::LinkedList<Customer*>();
}

Manager::~Manager()
{
	delete potatoes;
	delete oil;
	delete flavouring;

	delete tomorrowsPotatoes;
	delete tomorrowsOil;
	delete tomorrowsFlavouring;

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

Customer & Manager::getCustomer(std::string name)
{
	for each (Customer* c in *customers)
	{
		if (c->getName().compare(name) == 0)
		{
			return *c;
		}
	}
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
	order.setRecordDate(TODAY);
	if (order.getDeliveryDeathLine() - order.getRecordDate() < 7 * DAY_SEC)
	{
		order.notAccepted();
		return;
	}
	structures::LinkedList<Order&> *thatDay = getOrdersBetweenDays(orders, order.getDeliveryDeathLine(), order.getDeliveryDeathLine());
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
		|| name == ProductName::crisps && amountForDay + order.getProduct().getAmount() <= totalCapacityCrisps)
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
	structures::ArrayList<double> needs = getNeedsFor(TODAY + DAY_SEC, TODAY + 7 * DAY_SEC);

	if (needs[0] > potatoes->getAmount())
		tryToBuyGoods(Goods::potatoes, needs[0] - potatoes->getAmount());

	if (needs[1] > oil->getAmount())
		tryToBuyGoods(Goods::oil, needs[1] - oil->getAmount());

	if (needs[2] > flavouring->getAmount())
		tryToBuyGoods(Goods::flavouring, needs[2] - flavouring->getAmount());
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

//Have to delete object it returns! 
structures::LinkedList<Customer&> * Manager::getCustomers(int region)
{
	structures::LinkedList<Customer&> *ret = new structures::LinkedList<Customer&>();
	for (Customer *c : *customers) {
		if (c->getAddress() == region)
		{
			ret->add(*c);
		}
	}
	return ret;
}

void Manager::goToTomorrowReceiveGoods()
{
	TODAY += DAY_SEC;
	potatoes->addAmount(tomorrowsPotatoes->clear());
	oil->addAmount(tomorrowsOil->clear());
	flavouring->addAmount(tomorrowsFlavouring->clear());
}
