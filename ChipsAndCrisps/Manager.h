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

	structures::LinkedList<Supplier*> *suppliers;
	structures::LinkedList<Supplier*> potatoesSups;
	structures::LinkedList<Supplier*> oilSups;
	structures::LinkedList<Supplier*> flavouringSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityPotatoesSups; // after pop have to push immediately with updated avg price
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityOilSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> priorityFlavouringSups;

	structures::LinkedList<Vehicle*> *vehicles;
	structures::LinkedList<Vehicle&> chipsVehicles;
	structures::LinkedList<Vehicle&> crispsVehicles;

	structures::LinkedList<Customer*> *customers;

	structures::LinkedList<Order*> *orders;


	//--------------------------------
	structures::LinkedList<Goods> goods;
	structures::ArrayList<Product> products;

	void addAlphabetical(structures::LinkedList<BusinessPartner*> &list, BusinessPartner *supplier);
	void sortByGoods(Supplier *supplier);

	void addByDate(Vehicle *vehicle);

	void buyGoods();
	void cancelWorstOrders();

public:
	Manager(std::string companyName);
	~Manager();

	void addSupplier(Supplier *supplier);
	void addVehicle(Vehicle *vehicle);
	void addCustomer(Customer *customer);
	void addOrder(Order &order);
	Order& getBadOrders(time_t from, time_t to);
	Supplier& getBestSupplier();
	structures::LinkedList<Customer&> getCustomers(int region);
	Order& getGoodOrders(time_t from, time_t to);
	Order getNextDayOrders();
	int getProfit();
	structures::LinkedList<Supplier*>& getSuppliers() { return *suppliers; }
	structures::LinkedList<Supplier*>& getSuppliers(GoodsType type);
	//structures::PriorityQueueUnsortedArrayList<Supplier&> getPrioritySuppliers(GoodsType type);
	structures::LinkedList<Vehicle*> & getVehicles() { return *vehicles; }
	void goodsReceived();
	void goToTomorrow();
	Product checkOrders7days();
	void loadVehicles();
	void ordersDelivered();
	void produceOrders();
	time_t today();


};

