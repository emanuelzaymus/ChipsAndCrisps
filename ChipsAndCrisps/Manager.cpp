#include "structures\heap_monitor.h"

#include <string>
#include <algorithm>
#include <iostream>

#include "Manager.h"
#include "Product.h"

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

structures::ArrayList<double> Manager::getNeedsFor(time_t fromDay, time_t toDay)
{
	structures::ArrayList<double> needs;
	double neededPotatoes(0);
	double neededOil(0);
	double neededFlavouring(0);

	structures::LinkedList<Order&> * ordersFromTo = getOrdersBetweenDays(fromDay, toDay);
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
	structures::Heap<Supplier&> *s;
	Goods *tg;
	structures::Heap<Supplier&> popped;

	if (type == Goods::potatoes) {
		s = priorityPotatoesSups;
		tg = tomorrowsPotatoes;
	}
	else if (type == Goods::oil) {
		s = priorityOilSups;
		tg = tomorrowsOil;
	}
	else {
		s = priorityFlavouringSups;
		tg = tomorrowsFlavouring;
	}

	while (!s->isEmpty() && amount >= 0)
	{
		Supplier &sup = s->pop();
		amount -= sup.getGoods(type).getAmount();
		tg->addAmount(sup.buy(type).getAmount());

		popped.push(sup.getGoods(type).getRoundedAveragePrice(), sup);
	}

	int peekedPriority;
	while (!popped.isEmpty())
	{
		peekedPriority = popped.peekPriority();
		s->push(peekedPriority, popped.pop());
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
		cancelOrders(Goods::oil, tommorrowsNeeds[1] > oil->getAmount() - tomorrowsOil->getAmount());
		tommorrowsNeeds = getNeedsFor(TODAY + DAY_SEC, TODAY + DAY_SEC);
	}

	if (tommorrowsNeeds[2] > flavouring->getAmount() + tomorrowsFlavouring->getAmount())
		cancelOrders(Goods::flavouring, tommorrowsNeeds[2] - flavouring->getAmount() - tomorrowsFlavouring->getAmount());
}

void Manager::produceProducts()
{

}

void Manager::cancelOrders(Goods type, double howMuch)
{
	double cancelledAmount = 0;
	structures::LinkedList<Order&> *tomorrows = getOrdersBetweenDays(TODAY + DAY_SEC, TODAY + DAY_SEC);
	structures::Heap<Order&> smallestProfitTomorrow;

	int length = tomorrows->size();
	for (size_t i = 0; i < length; i++)
	{
		Order& o = tomorrows->removeAt(0);
		smallestProfitTomorrow.push((int)o.getTotalPrice(), o);
	}
	delete tomorrows;

	while (!smallestProfitTomorrow.isEmpty() && cancelledAmount < howMuch)
	{
		Order& o = smallestProfitTomorrow.pop();
		if (!(type == Goods::flavouring && o.getProduct().getName() != ProductName::crisps))
		{
			o.cancel();
			badOrders.add(o);
			cancelledAmount += o.getProduct().getAmount();
			orders.tryRemove(o);
		}
	}
}

structures::LinkedList<Order&>* Manager::getOrdersBetweenDays(time_t fromDay, time_t toDay)
{
	struct tm * dayInfo;
	dayInfo = localtime(&fromDay);
	int from_year = dayInfo->tm_year;
	int from_yday = dayInfo->tm_yday;
	dayInfo = localtime(&toDay);
	int to_year = dayInfo->tm_year;
	int to_yday = dayInfo->tm_yday;

	structures::LinkedList<Order&> *ret = new structures::LinkedList<Order&>();
	time_t deathLine;
	for (Order &o : orders)
	{
		deathLine = o.getDeliveryDeathLine();
		dayInfo = localtime(&deathLine);
		if (from_year <= dayInfo->tm_year && from_yday <= dayInfo->tm_yday && to_year >= dayInfo->tm_year && to_yday >= dayInfo->tm_yday)
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

	chips = new Product(ProductName::chips, 0);
	crisps = new Product(ProductName::crisps, 0);

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

	delete chips;
	delete crisps;

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
	order.setRecordDate(TODAY);
	if (order.getDeliveryDeathLine() - order.getRecordDate() < 7 * DAY_SEC)
	{
		order.setAccepted(false);
		return;
	}
	structures::LinkedList<Order&> *thatDay = getOrdersBetweenDays(order.getDeliveryDeathLine(), order.getDeliveryDeathLine());
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
		orders.add(order); // todo add by record date
		smallestProfitOrders.push((int)order.getTotalPrice(), order);
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
	structures::ArrayList<double> needs = getNeedsFor(TODAY, TODAY + 7 * DAY_SEC);

	if (needs[0] > potatoes->getAmount())
		tryToBuyGoods(Goods::potatoes, needs[0] - potatoes->getAmount());

	if (needs[1] > oil->getAmount())
		tryToBuyGoods(Goods::oil, needs[1] > oil->getAmount());

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

void Manager::goToTomorrowReceiveGoods()
{
	TODAY += DAY_SEC;
	potatoes->addAmount(tomorrowsPotatoes->clear());
	oil->addAmount(tomorrowsOil->clear());
	flavouring->addAmount(tomorrowsFlavouring->clear());
}
