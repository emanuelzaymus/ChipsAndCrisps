#pragma once

#include "structures\heap_monitor.h"

#include "Manager.h"

class CLI
{
	int printMenu();

	void simulateOneDay();

	void generateSuppliers();
	structures::ArrayList<SupplierGoods*> * generateSuppliersGoods();
	void generateVehicles();
	std::string generateRegNo();
	void generateCustomers();
	void generateOrders();

	void generate();

	void addSupplier();
	void printSuppliers();
	void addVehicle();
	void printVehicles();
	void addCustomer();
	void addOrder();
	void checkOrders7Days();
	void printOrders();
	void loadVehicles();
	void deliverOrders();
	void printCustomers();
	void printGoodOrders();
	void printBadOrders();
	void bestSupplier();
	void profit();

	void produceTomorrowsProducts();
	void printOrdersInHeap(structures::Heap<Order&> ords);
	void checkTomorrowsOrders();
	void goForward(int days);
	void goForwardDays();
	void today();
	void storehouse();

	Manager *manager;
public:
	CLI();
	~CLI();

	void run();
};

