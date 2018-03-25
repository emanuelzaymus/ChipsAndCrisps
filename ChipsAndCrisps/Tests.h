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

	bool testSupplier();
	void generateSuppliers();
	structures::ArrayList<SupplierGoods*> *generateSuppliersGoods();
	std::string randName();

	bool testVehicle();
	void generateVehicles();
	Vehicle * generateVehicle();
	std::string generateRegNo();

	bool testCustomer();
	void generateCustomers();

public:
	Tests();
	~Tests();

	bool test();
};

