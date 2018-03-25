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
	time_t today;
	double income = 0;
	double costs = 0;
	int totalCapacityCrisps = 0;
	int totalCapacityChips = 0;

	Goods *potatoes;
	Goods *oil;
	Goods *flavouring;

	structures::LinkedList<Supplier*> *suppliers;
	structures::LinkedList<Supplier*> potatoesSups;
	structures::LinkedList<Supplier*> oilSups;
	structures::LinkedList<Supplier*> flavouringSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> *priorityPotatoesSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> *priorityOilSups;
	structures::PriorityQueueUnsortedArrayList<Supplier&> *priorityFlavouringSups;

	structures::LinkedList<Vehicle*> *vehicles;
	structures::LinkedList<Vehicle&> chipsVehicles;
	structures::LinkedList<Vehicle&> crispsVehicles;

	structures::LinkedList<Customer*> *customers;

	structures::LinkedList<Order&> orders;
	structures::LinkedList<Order&> badOrders;


	//--------------------------------
	structures::LinkedList<Goods> goods;
	structures::ArrayList<Product> products;
	//--------------------------------

	void addAlphabetical(structures::LinkedList<BusinessPartner*> &list, BusinessPartner *supplier);
	void sortByGoods(Supplier *supplier);

	void addByDate(Vehicle * vehicle);
	void addByDate(structures::LinkedList<IRecordDateElem&> &list, IRecordDateElem &elem);
	structures::LinkedList<Order&> * getOrders7Days();

	void tryToBuyGoods(GoodsType type, double amount);
	void cancelWorstOrders(double neededPotatoes, double neededOil, double neededFlavouring);

public:
	Manager(std::string companyName);
	~Manager();

	structures::LinkedList<Supplier*>& getSuppliers() { return *suppliers; }
	structures::LinkedList<Supplier*>& getSuppliers(GoodsType type);
	//structures::PriorityQueueUnsortedArrayList<Supplier&> getPrioritySuppliers(GoodsType type);
	structures::LinkedList<Vehicle*> & getVehicles() { return *vehicles; }
	structures::LinkedList<Customer&> getCustomers(int region);
	structures::LinkedList<Customer*>& getCustomers() { return *customers; };
	structures::LinkedList<Order&> * getDayOrders(time_t day0000);
	structures::LinkedList<Order&> & getOrders() { return orders; }


	void addSupplier(Supplier *supplier);
	void addVehicle(Vehicle *vehicle);
	void addCustomer(Customer *customer);
	void addOrder(Order &order);

	void receiveOrders();
	void checkOrders7days();

	Order& getBadOrders(time_t from, time_t to);
	Order& getGoodOrders(time_t from, time_t to);
	Supplier& getBestSupplier();
	void goodsReceived();
	void loadVehicles();
	void ordersDelivered();
	void produceOrders();


	time_t getToday() { return today; }
	void goToTomorrow() { today += 24 * 60 * 60; }
	double getProfit() { return income - costs; }
};

