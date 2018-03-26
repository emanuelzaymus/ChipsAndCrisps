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
	static time_t today;
	double income = 0;
	double costs = 0;
	int totalCapacityCrisps = 0;
	int totalCapacityChips = 0;
public:
	Goods *potatoes;
	Goods *oil;
	Goods *flavouring;

	Goods *tomorrowsPotatoes;
	Goods *tomorrowsOil;
	Goods *tomorrowsFlavouring;
private:
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
	///// <summary> Have to delete object it returns! </summary>
	//structures::LinkedList<Order&> * getOrders7Days();

	void tryToBuyGoods(GoodsType type, double amount);
	void cancelTomorrowsWorstOrdersIfNecessary();

public:
	static const int DAY_SEC = 24 * 60 * 60;
	static int getToday();

	Manager(std::string companyName);
	~Manager();

	structures::LinkedList<Supplier*>& getSuppliers() { return *suppliers; }
	structures::LinkedList<Supplier*>& getSuppliers(GoodsType type);
	//structures::PriorityQueueUnsortedArrayList<Supplier&> getPrioritySuppliers(GoodsType type);
	structures::LinkedList<Vehicle*> & getVehicles() { return *vehicles; }
	structures::LinkedList<Customer&> getCustomers(int region);
	structures::LinkedList<Customer*>& getCustomers() { return *customers; };
	/// <summary> Have to delete object it returns! </summary>
	structures::LinkedList<Order&> * getOrdersBetweenDays(time_t fromDay, time_t toDay);
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
	void loadVehicles();
	void ordersDelivered();
	void produceOrders();


	void goToTomorrowReceiveGoods();
	double getProfit() { return income - costs; }
};

