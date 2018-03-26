#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"
#include "structures\list\linked_list.h"
#include "structures\array\array.h"
#include "structures\stack\explicit_stack.h"
#include "structures\priority_queue\priority_queue_unsorted_array_list.h"

#include "Tests.h"
#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"


bool Tests::testSupplier()
{
	generateSuppliers();

	structures::LinkedList<Supplier*>& sups = manager->getSuppliers();
	for (Supplier *s : sups) {
		std::cout << *s << std::endl;
	}

	std::cout << std::endl << "Suppliers of " << Goods::potatoes.name << std::endl;
	structures::LinkedList<Supplier*>& psups = manager->getSuppliers(Goods::potatoes);
	for (Supplier *s : psups) {
		std::cout << *s << std::endl;
	}
	std::cout << std::endl << "Suppliers of " << Goods::oil.name << std::endl;
	structures::LinkedList<Supplier*>& osups = manager->getSuppliers(Goods::oil);
	for (Supplier *s : osups) {
		std::cout << *s << std::endl;
	}
	std::cout << std::endl << "Suppliers of " << Goods::flavouring.name << std::endl;
	structures::LinkedList<Supplier*>& fsups = manager->getSuppliers(Goods::flavouring);
	for (Supplier *s : fsups) {
		std::cout << *s << std::endl;
	}

	if (sups.size() < 10 || sups.size() > 25)
	{
		return false;
	}
	return true;
}

void Tests::generateSuppliers()
{
	int countOfSuppliers = rand() % 15 + 10;
	for (size_t i = 0; i < countOfSuppliers; i++)
	{
		structures::ArrayList<SupplierGoods*> *suppliersGoods = generateSuppliersGoods();
		manager->addSupplier(new Supplier(randName(), suppliersGoods));
	}
}

structures::ArrayList<SupplierGoods*> * Tests::generateSuppliersGoods()
{
	structures::ArrayList<SupplierGoods*> * suppliersGoods = new structures::ArrayList<SupplierGoods*>();
	for (size_t i = 0; i < 3; i++)
	{
		if ((rand() % 2) == 0)
			continue;

		GoodsType type;
		switch (i + 1)
		{
		case 1:
			type = Goods::potatoes;
			break;
		case 2:
			type = Goods::oil;
			break;
		case 3:
			type = Goods::flavouring;
			break;
		}
		suppliersGoods->add(new SupplierGoods(type));
	}
	return suppliersGoods;
}

std::string Tests::randName()
{
	int count = rand() % 10 + 3;
	std::string name = "";
	name += char(rand() % 25 + 65);
	for (size_t i = 0; i < count; i++)
	{
		name += char(rand() % 25 + 97);
	}
	return name;
}

bool Tests::testVehicle()
{
	generateVehicles();

	structures::LinkedList<Vehicle*> &vehicles = manager->getVehicles();
	for (Vehicle *v : vehicles)
	{
		std::cout << *v;
	}
	return true;
}

void Tests::generateVehicles()
{
	int countOfVehicles = rand() % 10 + 10;
	for (size_t i = 0; i < countOfVehicles; i++)
	{
		manager->addVehicle(generateVehicle());
	}
}

Vehicle * Tests::generateVehicle()
{
	VehicleType type;
	if (rand() % 2)
		type = Vehicle::chipsType;
	else
		type = Vehicle::crispsType;

	Vehicle * newVehicle = new Vehicle(type, generateRegNo(), Manager::getToday());
	return newVehicle;
}

std::string Tests::generateRegNo()
{
	std::string regNo = "";
	for (size_t i = 0; i < 2; i++)
		regNo += char(rand() % 25 + 65);
	for (size_t i = 0; i < 3; i++)
		regNo += char(rand() % 9 + 48);
	for (size_t i = 0; i < 2; i++)
		regNo += char(rand() % 25 + 65);
	return regNo;
}

bool Tests::testCustomer()
{
	generateCustomers();
	for (size_t i = 1; i <= 8; i++)
	{
		std::cout << "Region " << i << std::endl;
		for (Customer &c : manager->getCustomers(i))
		{
			std::cout << c << std::endl;
		}
		std::cout << std::endl;
	}
	return true;
}

void Tests::generateCustomers()
{
	int countOfCustomers = rand() % 5 + 10;
	for (size_t i = 0; i < countOfCustomers; i++)
	{
		Customer *c = new Customer(randName(), rand() % 8 + 1);
		manager->addCustomer(c);
	}
}

bool Tests::testOrder()
{
	int howManyOrders;
	for (Customer *c : manager->getCustomers())
	{
		howManyOrders = rand() % 2 + 1;
		for (size_t i = 0; i < howManyOrders; i++)
		{
			c->createOrder(manager->getToday() + (rand() % 6 + 5) * Manager::DAY_SEC);
		}
	}
	manager->receiveOrders();

	for (Order &o : manager->getOrders())
	{
		std::cout << o;
	}

	std::cout << std::endl << "Orders in 8 days:" << std::endl;
	time_t day = manager->getToday() + 8 * Manager::DAY_SEC;
	structures::LinkedList<Order&>* thatDayOrders = manager->getOrdersBetweenDays(day, day);
	for (Order &o : *thatDayOrders)
	{
		std::cout << o;
	}
	delete thatDayOrders;

	std::cout << std::endl << "Orders in 9 days:" << std::endl;
	day = manager->getToday() + 9 * Manager::DAY_SEC;
	structures::LinkedList<Order&>* thatDayOrders2 = manager->getOrdersBetweenDays(day, day);
	for (Order &o : *thatDayOrders2)
	{
		std::cout << o;
	}
	delete thatDayOrders2;

	return true;
}

void Tests::testCheckOrders7days()
{
	manager->goToTomorrowReceiveGoods();
	manager->goToTomorrowReceiveGoods();
	manager->goToTomorrowReceiveGoods();

	std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	std::cout << std::endl;

	manager->checkOrders7days();
	std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	std::cout << std::endl;

	manager->goToTomorrowReceiveGoods();
	std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	std::cout << std::endl;

}

Tests::Tests()
{
	manager = new Manager("Chips And Crisps");
}


Tests::~Tests()
{
	delete manager;
}

bool Tests::test()
{

	bool supplier = testSupplier();
	if (supplier)
		std::cout << std::endl << "Supplier tests OK" << std::endl << std::endl;
	else
		std::cout << std::endl << "Supplier tests WENT BAD" << std::endl << std::endl;

	bool vehicle = testVehicle();
	if (vehicle)
		std::cout << std::endl << "Vehicle tests OK" << std::endl << std::endl;
	else
		std::cout << std::endl << "Vehicle tests WENT BAD" << std::endl << std::endl;

	bool customer = testCustomer();
	if (customer)
		std::cout << std::endl << "Customer tests OK" << std::endl << std::endl;
	else
		std::cout << std::endl << "Customer tests WENT BAD" << std::endl << std::endl;

	bool order = testOrder();
	if (order)
		std::cout << std::endl << "Order tests OK" << std::endl << std::endl;
	else
		std::cout << std::endl << "Order tests WENT BAD" << std::endl << std::endl;

	testCheckOrders7days();

	//testCancellingOrders();

	//struct tm * timeinfo;

	//time_t day = time(NULL);

	//time(&day);
	//timeinfo = localtime(&day);
	/*asctime(timeinfo)*/;

	//std::cout << asctime(timeinfo) << std::endl;

	//std::cout << timeinfo->tm_year << std::endl;
	//std::cout << timeinfo->tm_mon << std::endl;
	//std::cout << timeinfo->tm_mday << std::endl;


	//day += 365*Manager::DAY_SEC;
	//timeinfo = localtime(&day);

	//std::cout << timeinfo->tm_year << std::endl;
	//std::cout << timeinfo->tm_mon << std::endl;
	//std::cout << timeinfo->tm_mday << std::endl;

	/*time_t day2 = manager->getToday() + 5000;

	time(&day2);
	timeinfo = gmtime(&day2);


	std::cout << timeinfo->tm_year << std::endl;
	std::cout << timeinfo->tm_mon << std::endl;
	std::cout << timeinfo->tm_mday << std::endl;*/

	

	return true;
}
