#pragma once

#include <string>
#include <ostream>

#include "structures\heap_monitor.h"
#include "structures\queue\explicit_queue.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"

//#include "Order.h"
#include "BusinessPartner.h"

class Order;

class Customer : public BusinessPartner
{
private:
	structures::LinkedList<Order*> *orders;
	structures::ExplicitQueue<Order&> waitingOrders;
	structures::LinkedList<Order&> goodOrders;
	structures::LinkedList<Order&> badOrders;

	int address;
	int incomeFromCustomer = 0;

public:
	Customer(std::string name, int address);
	~Customer();

	void createOrder(time_t deliveryDeathLine);
	bool hasOrder() { return !waitingOrders.isEmpty(); }
	Order& getOrder() { return waitingOrders.pop(); }
	int getAddress() { return address; }
	void addRejectedOrder(Order &rejected) { badOrders.add(rejected); }

	friend std::ostream& operator<< (std::ostream &strm, const Customer &obj);
	friend bool operator==(const Customer& lhs, const Customer& rhs);
};


inline std::ostream& operator<< (std::ostream &strm, const Customer &obj) {
	return strm << obj.getFormattedName() << "  (" << obj.address << ")";
}

inline bool operator==(const Customer& lhs, const Customer& rhs) { return lhs.name == rhs.name; }