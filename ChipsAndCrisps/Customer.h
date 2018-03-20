#pragma once

#include <string>
#include <ostream>

#include "Order.h"

class Customer
{
private:
	int address;
	int incomeFromCustomer = 0;
	std::string name;
	//Order orders[];

public:
	Customer();
	~Customer();

	friend std::ostream& operator<< (std::ostream &strm, const Customer &obj);
};


inline std::ostream& operator<< (std::ostream &strm, const Customer &obj) {
	return strm << obj.name;
}