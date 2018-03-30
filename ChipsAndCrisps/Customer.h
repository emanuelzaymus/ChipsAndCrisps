#pragma once

#include <string>
#include <ostream>

#include "structures\heap_monitor.h"
#include "structures\queue\explicit_queue.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"

//#include "Order.h"
#include "BusinessPartner.h"
//#include "Manager.h"

class Order;
//class Manager;

class Customer : public BusinessPartner
{
private:
	structures::LinkedList<Order*> *orders;
	structures::ExplicitQueue<Order&> waitingOrders;
	structures::LinkedList<Order&> goodOrders;
	structures::LinkedList<Order&> rejectedOrders;
	structures::LinkedList<Order&> cancelledOrders;

	int address;
	double incomeFromCustomer = 0;

	int getWeight(structures::LinkedList<Order&> &ords);
	double getPrice(structures::LinkedList<Order&> &ords);

public:
	Customer(std::string name, int address);
	~Customer();

	void createOrder(time_t deliveryDeathLine);
	void addOrder(Order *order);
	bool hasOrder() { return !waitingOrders.isEmpty(); }
	Order& getOrder() { return waitingOrders.pop(); }
	int getAddress() { return address; }
	void addRejectedOrder(Order &rejected) { rejectedOrders.add(rejected); }
	void addCancelledOrder(Order &cancelled) { cancelledOrders.add(cancelled); }
	void addGoodOrder(Order &good);
	double getIncomeFromTo(time_t from, time_t to);

	std::string about(time_t fromDay, time_t toDay);

	friend std::ostream& operator<< (std::ostream &strm, const Customer &obj);
	friend bool operator==(const Customer& lhs, const Customer& rhs);
};


inline std::ostream& operator<< (std::ostream &strm, const Customer &obj) {
	return strm << obj.getFormattedName() << "  (" << obj.address << ")";
}

inline bool operator==(const Customer& lhs, const Customer& rhs) { return lhs.name == rhs.name; }