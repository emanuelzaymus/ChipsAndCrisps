#include "CLI.h"

#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"
#include <iostream>
#include <cstdlib>

#include "Vehicle.h"


int CLI::printMenu()
{
	std::cout << " 0 - Simulate One Day" << std::endl << std::endl;

	std::cout << " 1 - Add Supplier" << std::endl;
	std::cout << " 2 - Print Suppliers" << std::endl;
	std::cout << " 3 - Add Vehicle" << std::endl;
	std::cout << " 4 - Print Vehicles" << std::endl;
	std::cout << " 5 - Add Customer" << std::endl;
	std::cout << " 6 - Add Order" << std::endl;
	std::cout << " 7 - Check Orders for 7 Days" << std::endl;
	std::cout << " 8 - Print Orders" << std::endl;
	std::cout << " 9 - Load Vehicles" << std::endl;
	std::cout << "10 - Deliver Orders" << std::endl;
	std::cout << "11 - Print Customers" << std::endl;
	std::cout << "12 - Print Successful Orders" << std::endl;
	std::cout << "13 - Print Failed Orders" << std::endl;
	std::cout << "14 - Print The Best Supplier" << std::endl;
	std::cout << "15 - Print Profit" << std::endl << std::endl;

	std::cout << "16 - Produce Products For Tomorrows +" << std::endl;
	std::cout << "17 - Check Tomorrows Orders (cancel if necessary)" << std::endl;
	std::cout << "18 - Go To Tomorrow, Receive Goods From Suppliers" << std::endl;
	std::cout << "19 - Go Forward (days), Receive Goods" << std::endl;
	std::cout << "20 - Generate Everything (generate random values)" << std::endl;
	std::cout << "21 - Generate More Orders" << std::endl;
	std::cout << "22 - Today" << std::endl;
	std::cout << "23 - Storehouse" << std::endl;
	std::cout << "24 - End" << std::endl;

	int choice;
	std::cin >> choice;
	system("cls");
	return choice;
}

void CLI::simulateOneDay()
{
	generate();

	//printSuppliers();
	//printVehicles();
	//printCustomers();
	//printOrders();

	today();	storehouse();
	goForward(5);
	today();	storehouse();

	checkOrders7Days();
	today();	storehouse();

	goForward(1);
	today();	storehouse();

	checkTomorrowsOrders();
	produceTomorrowsProducts();
	today();	storehouse();

	loadVehicles();
	deliverOrders();
	profit();
}

void CLI::generateSuppliers()
{
	int countOfSuppliers = rand() % 15 + 10;
	for (size_t i = 0; i < 10; i++)
	{
		std::string name = "BioFarmer" + std::to_string(i);
		structures::ArrayList<SupplierGoods*> *suppliersGoods = generateSuppliersGoods();
		manager->addSupplier(new Supplier(name, suppliersGoods));
	}
}

structures::ArrayList<SupplierGoods*> * CLI::generateSuppliersGoods()
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

void CLI::generateVehicles()
{
	//manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));

	//manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::chipsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));
	//manager->addVehicle(new Vehicle(Vehicle::crispsType, generateRegNo(), Manager::TODAY));


	int countOfVehicles = rand() % 5 + 5;
	for (size_t i = 0; i < countOfVehicles; i++)
	{
		VehicleType type;
		if (rand() % 2)
			type = Vehicle::chipsType;
		else
			type = Vehicle::crispsType;
		manager->addVehicle(new Vehicle(type, generateRegNo(), Manager::TODAY));
	}
}

std::string CLI::generateRegNo()
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

void CLI::generateCustomers()
{
	//manager->addCustomer(new Customer("Fero", 1));
	//manager->addCustomer(new Customer("Patrik", 1));
	//manager->addCustomer(new Customer("John", 1));
	//manager->addCustomer(new Customer("Marek", 1));
	//manager->addCustomer(new Customer("Palo", 1));
	//manager->addCustomer(new Customer("Jan", 1));
	//manager->addCustomer(new Customer("Dusan", 1));
	//manager->addCustomer(new Customer("Lukas", 1));
	//manager->addCustomer(new Customer("Tomas", 1));
	//manager->addCustomer(new Customer("Matus", 1));

	int countOfCustomers = rand() % 5 + 10;
	for (size_t i = 0; i < countOfCustomers; i++)
	{
		std::string name = "Customer" + std::to_string(i);
		Customer *c = new Customer(name, rand() % 8 + 1);
		manager->addCustomer(c);
	}
}

void CLI::generateOrders()
{
	int howManyOrders;
	for (Customer *c : manager->getCustomers())
	{
		//c->addOrder(new Order(*c, Product(ProductName::chips, 900), 4, Manager::TODAY + 7 * Manager::DAY_SEC));
		//c->addOrder(new Order(*c, Product(ProductName::crisps, 900), 4, Manager::TODAY + 7 * Manager::DAY_SEC));

		//c->addOrder(new Order(*c, Product(ProductName::chips, 900), 4, Manager::TODAY + 7 * Manager::DAY_SEC));
		//c->addOrder(new Order(*c, Product(ProductName::crisps, 900), 4, Manager::TODAY + 7 * Manager::DAY_SEC));
		//c->addOrder(new Order(*c, Product(ProductName::chips, 900), 4, Manager::TODAY + 8 * Manager::DAY_SEC));
		//c->addOrder(new Order(*c, Product(ProductName::crisps, 900), 4, Manager::TODAY + 8 * Manager::DAY_SEC));

		howManyOrders = rand() % 2 + 1;
		for (size_t i = 0; i < howManyOrders; i++)
		{
			c->createOrder(Manager::TODAY + (rand() % 6 + 5) * Manager::DAY_SEC);
		}
	}
}

void CLI::generate()
{
	generateSuppliers();
	generateVehicles();
	generateCustomers();
	generateOrders();
	manager->receiveOrders();
	std::cout << "Random suppliers, vehicles, customers and orders hav been generated!" << std::endl;
	std::cin.ignore();
	std::cin.get();
}

void CLI::addSupplier()
{
	std::cout << "Name: ";
	std::string name;
	std::cin >> name;

	std::cout << "Count of goods: ";
	int g;
	std::cin >> g;

	std::cout << "1 - Potatoes" << std::endl;
	std::cout << "2 - Oil" << std::endl;
	std::cout << "3 - Flavouring" << std::endl;

	structures::ArrayList<SupplierGoods*>*goods = new structures::ArrayList<SupplierGoods*>();
	for (size_t i = 0; i < g; i++)
	{
		std::cout << i + 1 << ". goods: ";
		int goodsName;
		std::cin >> goodsName;
		switch (goodsName)
		{
		case 1:
			goods->add(new SupplierGoods(Goods::potatoes));
			break;
		case 2:
			goods->add(new SupplierGoods(Goods::oil));
			break;
		case 3:
			goods->add(new SupplierGoods(Goods::flavouring));
			break;
		}
	}
	manager->addSupplier(new Supplier(name, goods));
}

void CLI::printSuppliers()
{
	std::cout << "1 - Suppliers for Potatoes" << std::endl;
	std::cout << "2 - Suppliers for Oil" << std::endl;
	std::cout << "3 - Suppliers for Flavouring" << std::endl;
	std::cout << "4 - All Suppliers" << std::endl;
	int ch;
	std::cin >> ch;
	std::cout << "      Suppliers" << std::endl;
	std::cout << "Name            - Porduct (average price from last 30 days)" << std::endl << std::endl;

	structures::LinkedList<Supplier*>& sups = manager->getSuppliers();
	switch (ch)
	{
	case 1:
		std::cout << std::endl << "Suppliers for " << Goods::potatoes.name << std::endl;
		sups = manager->getSuppliers(Goods::potatoes);
		break;
	case 2:
		std::cout << std::endl << "Suppliers for " << Goods::oil.name << std::endl;
		sups = manager->getSuppliers(Goods::oil);
		break;
	case 3:
		std::cout << std::endl << "Suppliers for " << Goods::flavouring.name << std::endl;
		sups = manager->getSuppliers(Goods::flavouring);
		break;
	}
	for (Supplier *s : sups) {
		std::cout << *s << std::endl;
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::addVehicle()
{
	std::cout << "1 - Vehicle for chips" << std::endl;
	std::cout << "2 - Vehicle for crisps" << std::endl;
	int ch;
	std::cin >> ch;
	VehicleType type = Vehicle::chipsType;
	if (ch != 1)
	{
		type = Vehicle::crispsType;
	}
	std::cout << "Registration number: ";
	std::string regNo;
	std::cin >> regNo;
	manager->addVehicle(new Vehicle(type, regNo, Manager::TODAY));
}

void CLI::printVehicles()
{
	std::cout << "      Vehicles" << std::endl;
	std::cout << "Reg.No.  Type               Costs  Date of registration" << std::endl << std::endl;
	structures::LinkedList<Vehicle*> &vehicles = manager->getVehicles();
	for (Vehicle *v : vehicles)
	{
		std::cout << *v;
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::addCustomer()
{
	std::cout << "Name: ";
	std::string name;
	std::cin >> name;
	std::cout << "Region (1-8):";
	int region;
	std::cin >> region;
	manager->addCustomer(new Customer(name, region));
}

void CLI::addOrder()
{
	std::cout << "Name of customer: ";
	std::string name;
	std::cin >> name;
	Customer& customer = manager->getCustomer(name);
	std::cout << "1 - Chips" << std::endl;
	std::cout << "2 - Crisps" << std::endl;
	int product;
	std::cin >> product;
	ProductName productNme = ProductName::chips;
	if (product == 2)
	{
		productNme = ProductName::crisps;
	}
	std::cout << "How much: ";
	int amount;
	std::cin >> amount;

	std::cout << "Unit price: ";
	double price;
	std::cin >> price;

	std::cout << "In how many days: ";
	int days;
	std::cin >> days;

	Customer * c = &customer;
	Order * order = new Order(c, Product(productNme, amount), price, Manager::TODAY + days * Manager::DAY_SEC);
	customer.addOrder(order);
	manager->addOrder(customer.getOrder());
}

void CLI::checkOrders7Days()
{
	std::cout << "      Checked orders" << std::endl;
	manager->checkOrders7days();
	structures::LinkedList<Order&>* ords = manager->getOrdersBetweenDays(manager->getOrders(), Manager::TODAY, Manager::TODAY + 7 * Manager::DAY_SEC);
	for each (Order& ord in *ords)
	{
		std::cout << ord;
	}
	delete ords;
	std::cin.ignore();
	std::cin.get();
}

void CLI::printOrders()
{
	std::cout << "1 - Choose a day" << std::endl;
	std::cout << "2 - All Orders" << std::endl;
	int ch;
	std::cin >> ch;

	if (ch == 1)
	{
		std::cout << "Day: ";
		int chooseDay;
		std::cin >> chooseDay;
		std::cout << "      Orders" << std::endl;

		time_t day = Manager::TODAY + chooseDay * Manager::DAY_SEC;
		structures::LinkedList<Order&>* thatDayOrders = manager->getOrdersBetweenDays(manager->getOrders(), day, day);
		for (Order &o : *thatDayOrders)
		{
			std::cout << o;
		}
		delete thatDayOrders;
	}
	else {
		std::cout << "      Orders" << std::endl;
		std::cout << "Name           Region Product  kg   Price   Total    Record Date" << std::endl << std::endl;
		for (Order &o : manager->getOrders())
		{
			std::cout << o;
		}
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::loadVehicles()
{
	manager->loadVehicles();

	structures::LinkedList<Vehicle*> &vehicles = manager->getVehicles();
	for (Vehicle *veh : vehicles)
	{
		int totalLoadedAmount = 0;
		std::cout << *veh;
		structures::ExplicitStack<Order&> orders = veh->getOrders();
		while (!orders.isEmpty())
		{
			Order& ord = orders.pop();
			std::cout << "  " << ord;
			totalLoadedAmount += ord.getProduct().getAmount();
		}
		std::cout << "Total loaded amount: " << totalLoadedAmount << std::endl << std::endl;
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::deliverOrders()
{
	std::cout << "Orders were delivered." << std::endl;
	structures::LinkedList<Order&> & sent = manager->getSentOrders();
	for each (Order& ord in sent)
	{
		std::cout << ord;
	}
	manager->ordersDelivered();
	std::cin.ignore();
	std::cin.get();
}

void CLI::printCustomers()
{
	std::cout << " 1 - Make a choice from regions" << std::endl;
	std::cout << " 2 - All Customers" << std::endl;
	int ch;
	std::cin >> ch;
	if (ch == 1)
	{
		std::cout << "Region: ";
		int region;
		std::cin >> region;
		std::cout << "      Customers" << std::endl;

		structures::LinkedList<Customer&> * custReg = manager->getCustomers(region);
		for each (Customer &c in *custReg)
		{
			std::cout << c.about(Manager::TODAY - 365 * Manager::DAY_SEC, Manager::TODAY) << std::endl;
		}
	}
	else {
		std::cout << "      Customers" << std::endl;

		structures::LinkedList<Customer*> & cust = manager->getCustomers();
		for each (Customer *c in cust)
		{
			std::cout << c->about(Manager::TODAY - 365 * Manager::DAY_SEC, Manager::TODAY) << std::endl;
		}
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::printGoodOrders()
{
	std::cout << " 1 - Select Days" << std::endl;
	std::cout << " 2 - All Successful orders" << std::endl;
	int ch;
	std::cin >> ch;
	if (ch == 1) {
		std::cout << "Day from: ";
		int from;
		std::cin >> from;
		std::cout << "Day to: ";
		int to;
		std::cin >> to;
		std::cout << "      Successful orders" << std::endl;

		structures::LinkedList<Order&> * goodOnes = manager->getOrdersBetweenDays(manager->getGoodOrders(), Manager::TODAY - from * Manager::DAY_SEC, Manager::TODAY + to * Manager::DAY_SEC);
		for each (Order &ord in *goodOnes)
		{
			std::cout << ord.about();
		}
		delete goodOnes;
	}
	else {
		std::cout << "      Successful orders" << std::endl;

		structures::LinkedList<Order&> & goodOnes = manager->getGoodOrders();
		for each (Order &ord in goodOnes)
		{
			std::cout << ord.about();
		}
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::printBadOrders()
{
	std::cout << " 1 - Select Days" << std::endl;
	std::cout << " 2 - All Failed orders" << std::endl;
	int ch;
	std::cin >> ch;
	if (ch == 1) {
		std::cout << "Day from: ";
		int from;
		std::cin >> from;
		std::cout << "Day to: ";
		int to;
		std::cin >> to;
		std::cout << "      Failed orders" << std::endl;

		structures::LinkedList<Order&> * badOnes = manager->getOrdersBetweenDays(manager->getBadOrders(), Manager::TODAY - from * Manager::DAY_SEC, Manager::TODAY + to * Manager::DAY_SEC);
		for each (Order &ord in *badOnes)
		{
			std::cout << ord.about();
		}
		delete badOnes;
	}
	else {
		std::cout << "      Failed orders" << std::endl;

		structures::LinkedList<Order&> & badOnes = manager->getBadOrders();
		for each (Order &ord in badOnes)
		{
			std::cout << ord.about();
		}
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::bestSupplier()
{
	std::cout << " 1 - From potatoes" << std::endl;
	std::cout << " 2 - Form oil" << std::endl;
	std::cout << " 3 - Form flavouring" << std::endl;
	int ch;
	std::cin >> ch;
	GoodsType type;
	if (ch == 1)
		type = Goods::potatoes;
	else if (ch == 2)
		type = Goods::oil;
	else
		type = Goods::flavouring;
	try {
		Supplier &supPotatoes = manager->getBestSupplier(type);
		std::cout << "Best " << type.name << " supplier:" << std::endl;
		std::cout << supPotatoes.aboutBest(Goods::potatoes) << std::endl;
	}
	catch (const std::exception&) {
		std::cout << "No suppliers" << std::endl;
	}
	std::cin.ignore();
	std::cin.get();
}

void CLI::profit()
{
	std::cout << "Costs: " << manager->getCosts() << std::endl;
	std::cout << "Income: " << manager->getIncome() << std::endl;
	std::cout << "Profit: " << manager->getProfit() << std::endl;
	std::cin.ignore();
	std::cin.get();
}

void CLI::produceTomorrowsProducts()
{
	manager->produceTomorrowsProducts();
	std::cout << "Produced orders:" << std::endl;
	printOrdersInHeap(manager->getProducedOrdersChips());
	printOrdersInHeap(manager->getProducedOrdersCrisps());
	printOrdersInHeap(manager->getExtraProducedOrdersChips());
	printOrdersInHeap(manager->getExtraProducedOrdersCrisps());
	std::cin.ignore();
	std::cin.get();
}

void CLI::printOrdersInHeap(structures::Heap<Order&> ords)
{
	while (!ords.isEmpty())
	{
		std::cout << ords.pop();
	}
}

void CLI::checkTomorrowsOrders()
{
	manager->checkTomorrowsOrders();
	std::cout << "Tomorrows orders were checked." << std::endl;
	std::cin.ignore();
	std::cin.get();
}

void CLI::goForward(int days)
{
	for (size_t i = 0; i < days; i++)
	{
		manager->goToTomorrowReceiveGoods();
	}
	char date[30];
	sprintf(date, "%s", ctime(&Manager::TODAY));
	std::cout << "You went " << days << " forward and received goods from suppliers. It is: " << date << std::endl;
	std::cin.ignore();
	std::cin.get();
}

void CLI::goForwardDays()
{
	std::cout << "How many days: ";
	int days;
	std::cin >> days;
	goForward(days);
}

void CLI::today()
{
	char date[30];
	sprintf(date, "%s", ctime(&Manager::TODAY));
	std::cout << date << std::endl;
	std::cin.ignore();
	std::cin.get();
}

void CLI::storehouse()
{

	std::cout << "StoreHouse:" << std::endl;
	std::cout << manager->getPotataoes().getType().name << ": " << manager->getPotataoes().getAmount() << std::endl;
	std::cout << manager->getOil().getType().name << ": " << manager->getOil().getAmount() << std::endl;
	std::cout << manager->getFlavouring().getType().name << ": " << manager->getFlavouring().getAmount() << std::endl;

	std::cout << "StoreHouse (TOMORROW):" << std::endl;
	std::cout << manager->getTomorrPotatoes().getType().name << ": " << manager->getTomorrPotatoes().getAmount() << std::endl;
	std::cout << manager->getTomorrOil().getType().name << ": " << manager->getTomorrOil().getAmount() << std::endl;
	std::cout << manager->getTomorrFlavouring().getType().name << ": " << manager->getTomorrFlavouring().getAmount() << std::endl;
	std::cin.ignore();
	std::cin.get();
}

CLI::CLI()
{
	manager = new Manager("Chips And Crisps");
}


CLI::~CLI()
{
	delete manager;
}

void CLI::run()
{
	bool running = true;
	do
	{
		int choice = printMenu();

		switch (choice)
		{
		case 0: simulateOneDay(); break;

		case 1: addSupplier(); break;
		case 2: printSuppliers(); break;
		case 3: addVehicle(); break;
		case 4: printVehicles(); break;
		case 5: addCustomer(); break;
		case 6: addOrder(); break;
		case 7: checkOrders7Days(); break;
		case 8: printOrders(); break;
		case 9: loadVehicles(); break;
		case 10: deliverOrders(); break;
		case 11: printCustomers(); break;
		case 12: printGoodOrders(); break;
		case 13: printBadOrders(); break;
		case 14: bestSupplier(); break;
		case 15: profit(); break;

		case 16: produceTomorrowsProducts(); break;
		case 17: checkTomorrowsOrders(); break;
		case 18: goForward(1); break;
		case 19: goForwardDays(); break;
		case 20: generate(); break;
		case 21: generateOrders(); break;
		case 22: today(); break;
		case 23: storehouse(); break;
		case 24: running = false; break;
		}
		system("cls");

	} while (running);
}
