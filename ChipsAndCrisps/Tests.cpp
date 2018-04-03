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

//#include <Windows.h>

void Tests::testSupplier()
{
	generateSuppliers();

	printSuppliers();


}

void Tests::printSuppliers()
{
	std::cout << std::endl;
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
}

void Tests::generateSuppliers()
{
	int countOfSuppliers = rand() % 15 + 10;
	for (size_t i = 0; i < 25; i++)
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

void Tests::testVehicle()
{
	//generateVehicles();
	manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));
	manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));

	structures::LinkedList<Vehicle*> &vehicles = manager->getVehicles();

}

void Tests::generateVehicles()
{
	int countOfVehicles = rand() % 5 + 5;
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

	Vehicle * newVehicle = new Vehicle(type, generateRegNo(), Manager::TODAY);
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

void Tests::testCustomer()
{
	generateCustomers();
	for (size_t i = 1; i <= 8; i++)
	{
		std::cout << "Region " << i << std::endl;
		structures::LinkedList<Customer&> *customers = manager->getCustomers(i);
		for (Customer &c : *customers)
			std::cout << c << std::endl;

		delete customers;
		std::cout << std::endl;
	}
}

void Tests::generateCustomers()
{
	//int countOfCustomers = rand() % 5 + 10;
	//for (size_t i = 0; i < countOfCustomers; i++)
	//{
	//	Customer *c = new Customer(randName(), rand() % 8 + 1);
	//	manager->addCustomer(c);
	//}
	manager->addCustomer(new Customer("Fero", 1));
	manager->addCustomer(new Customer("Patrik", 1));
	manager->addCustomer(new Customer("John", 1));
	manager->addCustomer(new Customer("Marek", 1));
	manager->addCustomer(new Customer("Palo", 1));
	manager->addCustomer(new Customer("Jan", 1));
	manager->addCustomer(new Customer("Dusan", 1));
	manager->addCustomer(new Customer("Lukas", 1));
	manager->addCustomer(new Customer("Tomas", 1));
	manager->addCustomer(new Customer("Matus", 1));
}

void Tests::testOrder()
{
	int howManyOrders;
	for (Customer *c : manager->getCustomers())
	{
		//howManyOrders = rand() % 2 + 1;
		//for (size_t i = 0; i < 5; i++)
		//{
			//c->createOrder(Manager::TODAY + (rand() % 6 + 5) * Manager::DAY_SEC);
			//c->createOrder(Manager::TODAY + 8 * Manager::DAY_SEC);
		c->addOrder(new Order(c, Product(ProductName::chips, 900), 4, Manager::TODAY + 8 * Manager::DAY_SEC));
		c->addOrder(new Order(c, Product(ProductName::crisps, 900), 4, Manager::TODAY + 8 * Manager::DAY_SEC));
		//}
	}
	manager->receiveOrders();

	for (Order &o : manager->getOrders())
	{
		std::cout << o;
	}

	std::cout << std::endl << "Orders in 8 days:" << std::endl;
	time_t day = Manager::TODAY + 8 * Manager::DAY_SEC;
	structures::LinkedList<Order&>* thatDayOrders = manager->getOrdersBetweenDays(manager->getOrders(), day, day);
	for (Order &o : *thatDayOrders)
	{
		std::cout << o;
	}
	delete thatDayOrders;

	std::cout << std::endl << "Orders in 9 days:" << std::endl;
	day = Manager::TODAY + 9 * Manager::DAY_SEC;
	structures::LinkedList<Order&>* thatDayOrders2 = manager->getOrdersBetweenDays(manager->getOrders(), day, day);
	for (Order &o : *thatDayOrders2)
	{
		std::cout << o;
	}
	delete thatDayOrders2;

}

void Tests::testCheckOrders7days()
{
	manager->goToTomorrowReceiveGoods();
	std::cout << "_____ 1 DAY FORWARD _____" << std::endl;

	std::cout << "Ordert for next 7 days: " << std::endl;
	structures::LinkedList<Order&>* sevenDays = manager->getOrdersBetweenDays(manager->getOrders(), Manager::TODAY, Manager::TODAY + 7 * Manager::DAY_SEC);
	for (Order &o : *sevenDays)
	{
		std::cout << o;
	}
	delete sevenDays;
	std::cout << std::endl;

	//std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	//std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	//std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	//std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	//std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	//std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	//std::cout << std::endl;

	//manager->checkOrders7days();
	//std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	//std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	//std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	//std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	//std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	//std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	//std::cout << std::endl;

	//std::cout << "_____ 1 DAY FORWARD _____" << std::endl;
	//manager->goToTomorrowReceiveGoods();
	//std::cout << "Potatoes: " << manager->potatoes->getAmount() << std::endl;
	//std::cout << "Oil: " << manager->oil->getAmount() << std::endl;
	//std::cout << "Flavouring: " << manager->flavouring->getAmount() << std::endl;
	//std::cout << "Tomorrows potatoes: " << manager->tomorrowsPotatoes->getAmount() << std::endl;
	//std::cout << "Tomorrows oil: " << manager->tomorrowsOil->getAmount() << std::endl;
	//std::cout << "Tomorrows flavouring: " << manager->tomorrowsFlavouring->getAmount() << std::endl;
	//std::cout << std::endl;

}

void Tests::testCheckTomorrowsOrders()
{
	std::cout << "_____ 5 DAYS FORWARD _____" << std::endl;
	for (size_t i = 0; i < 5; i++)
		manager->goToTomorrowReceiveGoods();

	std::cout << "Tomorrows order: " << std::endl;
	structures::LinkedList<Order&>* tomorrow = manager->getOrdersBetweenDays(manager->getOrders(), Manager::TODAY + Manager::DAY_SEC, Manager::TODAY + Manager::DAY_SEC);
	for (Order &o : *tomorrow)
	{
		std::cout << o;
	}
	delete tomorrow;
	std::cout << std::endl;

	manager->checkTomorrowsOrders();

	std::cout << "AFTER CANCELLING Tomorrows order: " << std::endl;
	structures::LinkedList<Order&>* tomorrow2 = manager->getOrdersBetweenDays(manager->getOrders(), Manager::TODAY + Manager::DAY_SEC, Manager::TODAY + Manager::DAY_SEC);
	for (Order &o : *tomorrow2)
	{
		std::cout << o;
	}
	delete tomorrow2;
	std::cout << std::endl;
}

void Tests::testLoadingVehicles()
{
	std::cout << "LOADED VEHICLES" << std::endl;
	manager->loadVehicles();

	structures::LinkedList<Vehicle*> &vehicles = manager->getVehicles();
	for (Vehicle *veh : vehicles)
	{
		int totalLoadedAmount = 0;
		std::cout << *veh << std::endl;
		structures::ExplicitStack<Order&> orders = veh->getOrders();
		while (!orders.isEmpty())
		{
			Order& ord = orders.pop();
			std::cout << "    " << ord;
			totalLoadedAmount += ord.getProduct().getAmount();
		}
		std::cout << "TOTAL LOADED AMOUNT: " << totalLoadedAmount << std::endl;
	}
}

void Tests::testOrdersDelivered()
{
	manager->ordersDelivered();
	std::cout << "GOOD Orders" << std::endl;

	structures::LinkedList<Order&> goodOrd = manager->getGoodOrders();
	for each (Order& ord in goodOrd)
	{
		std::cout << ord;
	}
}

void Tests::testPrintCustomers()
{
	std::cout << "---------------------------- ABOUT CUSTOMERS ----------------------------" << std::endl;
	structures::LinkedList<Customer*> & cust = manager->getCustomers();
	for each (Customer *c in cust)
	{
		std::cout << c->about(Manager::TODAY - 365 * Manager::DAY_SEC, Manager::TODAY) << std::endl;
	}
}

void Tests::testPrintGoodOrders()
{
	std::cout << "---------------------------- ABOUT GOOD ORDERS ----------------------------" << std::endl;
	structures::LinkedList<Order&> * goodOnes = manager->getOrdersBetweenDays(manager->getGoodOrders(), Manager::TODAY - 365 * Manager::DAY_SEC, Manager::TODAY);
	for each (Order &ord in *goodOnes)
	{
		std::cout << ord.about();
	}
	delete goodOnes;
}

void Tests::testPrintBadOrders()
{
	std::cout << "---------------------------- ABOUT BAD ORDERS ----------------------------" << std::endl;
	structures::LinkedList<Order&> * badOnes = manager->getOrdersBetweenDays(manager->getBadOrders(), Manager::TODAY - 365 * Manager::DAY_SEC, Manager::TODAY);
	for each (Order &ord in *badOnes)
	{
		std::cout << ord.about();
	}
	delete badOnes;
}

void Tests::testBestSuppliers()
{
	Supplier &supPotatoes = manager->getBestSupplier(Goods::potatoes);
	std::cout << "Best potatoes supplier:" << std::endl;
	std::cout << supPotatoes.aboutBest(Goods::potatoes) << std::endl;
	
	Supplier &supOil = manager->getBestSupplier(Goods::oil);
	std::cout << "Best oil supplier:" << std::endl;
	std::cout << supOil.aboutBest(Goods::oil) << std::endl;

	Supplier &supFlavo = manager->getBestSupplier(Goods::flavouring);
	std::cout << "Best flavouring supplier:" << std::endl;
	std::cout << supFlavo.aboutBest(Goods::flavouring) << std::endl << std::endl;
}

void Tests::printProfit()
{
	std::cout << "Costs: " << manager->getCosts() << std::endl;
	std::cout << "Income: " << manager->getIncome() << std::endl;
	std::cout << "Profit: "<< manager->getProfit() <<  std::endl;
}

Tests::Tests()
{
	manager = new Manager("Chips And Crisps");
}


Tests::~Tests()
{
	delete manager;
}

void Tests::test()
{
	testSupplier();

	testVehicle();

	testCustomer();

	testOrder();
	
	testCheckOrders7days();

	testCheckTomorrowsOrders();

	manager->produceTomorrowsProducts();
	testLoadingVehicles();

	testOrdersDelivered();

	testPrintCustomers();

	testPrintGoodOrders();

	testPrintBadOrders();

	printSuppliers();

	testBestSuppliers();

	printProfit();

}
