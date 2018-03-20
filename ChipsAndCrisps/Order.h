#pragma once

#include <ctime>
#include <ostream>

#include "Customer.h"
#include "Product.h"

class Order
{
private:
	bool cancelled = false;
	//Customer *customer;
	time_t deliveryDate;
	time_t deliveryDeathLine;
	bool done = false;
	int price;
	Product product;
	time_t recordDate;
	bool rejected = false;

public:
	Order();
	~Order();

	friend std::ostream& operator<<(std::ostream &strm, const Order &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const Order &obj) {
	return strm << obj.price;
}