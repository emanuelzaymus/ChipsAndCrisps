#pragma once

#include <string>
#include <ostream>

#include "structures\heap_monitor.h"
#include "structures\queue\explicit_queue.h"
#include "structures\list\linked_list.h"
#include "structures\list\array_list.h"

#include "Order.h"
#include "BusinessPartner.h"


class Customer : public BusinessPartner
{
private:
	structures::ExplicitQueue<Order*> *waitingOrders;
	//structures::LinkedList<Order*> *goodOrders;
	//structures::LinkedList<Order*> *badOrders;

	int address;
	int incomeFromCustomer = 0;

public:
	Customer(std::string name, int address);
	~Customer();

	void createOrder();
	bool hasOrder() { return waitingOrders->isEmpty(); }
	int getAddress() { return address; }

	friend std::ostream& operator<< (std::ostream &strm, const Customer &obj);
	friend bool operator==(const Customer& lhs, const Customer& rhs);
};


inline std::ostream& operator<< (std::ostream &strm, const Customer &obj) {
	return strm << obj.name << "  " << obj.address;
}

inline bool operator==(const Customer& lhs, const Customer& rhs) { return lhs.name == rhs.name; }