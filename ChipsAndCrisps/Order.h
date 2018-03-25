#pragma once

#include <ctime>
#include <ostream>

#include "structures\heap_monitor.h"

#include "Product.h"

class Customer;

class Order
{
private:
	Customer &customer;
	Product product;
	double price;
	time_t recordDate;
	time_t deliveryDeathLine;
	time_t deliveryDate;
	bool done = false;
	bool cancelled = false;
	bool rejected = false;

public:
	Order(Customer &customer, Product product, double price, time_t recordDate, time_t deliveryDeathLine);
	~Order();

	friend std::ostream& operator<<(std::ostream &strm, const Order &obj);
	friend bool operator==(const Order& lhs, const Order& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Order &obj) {
	return strm << obj.price;
}
