#pragma once

#include <ctime>
#include <string>

#include "structures\heap_monitor.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"
#include "structures\priority_queue\priority_queue_unsorted_array_list.h"

#include "Customer.h"
#include "Goods.h"
#include "Order.h"
#include "Product.h"
#include "Supplier.h"
#include "Vehicle.h"


class Manager
{
private:
	std::string companyName;
	int income = 0;
	int costs = 0;
	int totalCapacityCrisps = 0;
	int totalCapacityChips = 0;

	structures::LinkedList<Supplier&> *suppliers;
	structures::LinkedList<Supplier&> potatoesSups;
	structures::LinkedList<Supplier&> oilSups;
	structures::LinkedList<Supplier&> flavouringSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityPotatoesSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityOilSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityFlavouringSups;

	structures::LinkedList<Goods> goods;
	structures::LinkedList<Customer> customer;
	structures::LinkedList<Order> orders;
	structures::ArrayList<Product> products;
	structures::LinkedList<Vehicle> vehicles;

	void addAlphabetical(structures::LinkedList<Supplier&> &list, Supplier &supplier);
	void sortByGoods(Supplier &supplier);
	bool buyGoods();
	void cancelWorstOrders();

public:
	Manager(std::string companyName);
	~Manager();

	void addSupplier(Supplier &supplier);
	void addCustomer(Customer &customer);
	void addOrder(Order &order);
	void addVehicle(Vehicle &vehicle);
	Order& getBadOrders(time_t from, time_t to);
	Supplier& getBestSupplier();
	Supplier getCustomers(int region);
	Order& getGoodOrders(time_t from, time_t to);
	Order getNextDayOrders();
	int getProfit();
	structures::LinkedList<Supplier&>& getSuppliers() { return *suppliers; }
	structures::LinkedList<Supplier&>& getSuppliers(GoodsType name);
	Vehicle getVehicles();
	void goodsReceived();
	void goToTomorrow();
	Product checkOrders7days();
	void loadVehicles();
	void ordersDelivered();
	void produceOrders();
	time_t today();


};

