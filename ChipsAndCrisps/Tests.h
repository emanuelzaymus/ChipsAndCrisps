#pragma once

#include <string>

#include "structures\heap_monitor.h"

#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"
#include "structures\list\linked_list.h"
#include "structures\array\array.h"
#include "structures\stack\explicit_stack.h"
#include "structures\priority_queue\priority_queue_unsorted_array_list.h"

#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"

class Tests
{
private:
	Manager *manager;

	void testSupplier();
	void printSuppliers();
	void generateSuppliers();
	structures::ArrayList<SupplierGoods*> *generateSuppliersGoods();
	std::string randName();

	void testVehicle();
	void generateVehicles();
	Vehicle * generateVehicle();
	std::string generateRegNo();

	void testCustomer();
	void generateCustomers();

	void testOrder();

	void testCheckOrders7days();
	void testCheckTomorrowsOrders();

	void testLoadingVehicles();
	void testOrdersDelivered();

	void testPrintCustomers();

	void testPrintGoodOrders();
	void testPrintBadOrders();

	void testBestSuppliers();

	void printProfit();

public:
	Tests();
	~Tests();

	void test();
};

