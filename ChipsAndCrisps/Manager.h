#pragma once

#include <ctime>
#include <string>

#include "structures\heap_monitor.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"
#include "structures\priority_queue\heap.h"

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
	double income = 0;
	double costs = 0;
	int totalCapacityCrisps = 0;
	int totalCapacityChips = 0;
public://temporary todo
	Goods *potatoes;
	Goods *oil;
	Goods *flavouring;

	Goods *tomorrowsPotatoes;
	Goods *tomorrowsOil;
	Goods *tomorrowsFlavouring;

	Product *chips;
	Product *crisps;

private://temporary todo
	structures::LinkedList<Supplier*> *suppliers;
	structures::LinkedList<Supplier*> potatoesSups;
	structures::LinkedList<Supplier*> oilSups;
	structures::LinkedList<Supplier*> flavouringSups;
	structures::Heap<Supplier&> *priorityPotatoesSups;
	structures::Heap<Supplier&> *priorityOilSups;
	structures::Heap<Supplier&> *priorityFlavouringSups;

	structures::LinkedList<Vehicle*> *vehicles;
	structures::LinkedList<Vehicle&> chipsVehicles;
	structures::LinkedList<Vehicle&> crispsVehicles;

	structures::LinkedList<Customer*> *customers;

	structures::LinkedList<Order&> orders;
	structures::LinkedList<Order&> badOrders;
	structures::Heap<Order&> producedOrdersChips;
	structures::Heap<Order&> producedOrdersCrisps;
	structures::Heap<Order&> extraProducedOrdersChips;
	structures::Heap<Order&> extraProducedOrdersCrisps;
	structures::LinkedList<Order&> sentOrders;
	//structures::LinkedList<Order&> goodOrders;

	//--------------------------------
	structures::ArrayList<Product> products;
	//--------------------------------

	void addAlphabetical(structures::LinkedList<BusinessPartner*> &list, BusinessPartner *supplier);
	void sortByGoods(Supplier *supplier);

	void addByDate(Vehicle * vehicle);
	void addByDate(structures::LinkedList<IRecordDateElem&> &list, IRecordDateElem &elem);

	structures::ArrayList<double> getNeedsFor(time_t fromDay, time_t toDay);
	void tryToBuyGoods(GoodsType type, double amount);
	void cancelOrders(Goods type, double howMuch);

	structures::LinkedList<Order&> * getOrdersBySpec(ProductName name, int howMuch, int region);

	void loadWithOrders(structures::LinkedList<Vehicle&> &vehiclesToLoad, structures::Heap<Order&> &ordersToLoad);

public:
	static time_t TODAY;
	static const int DAY_SEC = 24 * 60 * 60;

	Manager(std::string companyName);
	~Manager();

	structures::LinkedList<Supplier*> & getSuppliers() { return *suppliers; }
	structures::LinkedList<Supplier*> & getSuppliers(GoodsType type);
	structures::LinkedList<Vehicle*> & getVehicles() { return *vehicles; }
	structures::LinkedList<Customer&> getCustomers(int region);	//todo maybie bad return val
	structures::LinkedList<Customer*> & getCustomers() { return *customers; };
	structures::LinkedList<Order&> * getOrdersBetweenDays(time_t fromDay, time_t toDay);
	structures::LinkedList<Order&> & getOrders() { return orders; }



	void addSupplier(Supplier *supplier);
	void addVehicle(Vehicle *vehicle);
	void addCustomer(Customer *customer);
	void addOrder(Order &order);

	void receiveOrders();
	void checkOrders7days();
	void checkTomorrowsOrders();

	void produceTomorrowsProducts();
	void loadVehicles();
	

	void ordersDelivered();
	Order& getBadOrders(time_t from, time_t to);
	Order& getGoodOrders(time_t from, time_t to);
	Supplier& getBestSupplier();


	void goToTomorrowReceiveGoods();
	double getProfit() { return income - costs; }

	//--------------------------------------------------------
	structures::LinkedList<Order&> & getSentOrders() { return sentOrders; }

};

