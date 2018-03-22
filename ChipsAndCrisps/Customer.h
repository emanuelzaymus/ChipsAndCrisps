#pragma once

#include <string>
#include <ostream>

#include "structures\heap_monitor.h"

#include "Order.h"

class Customer
{
private:
	std::string name;
	int address;
	//Order orders[];
	int incomeFromCustomer = 0;

public:
	Customer();
	~Customer();

	friend std::ostream& operator<< (std::ostream &strm, const Customer &obj);
	friend bool operator==(const Customer& lhs, const Customer& rhs);
};


inline std::ostream& operator<< (std::ostream &strm, const Customer &obj) {
	return strm << obj.name;
}

inline bool operator==(const Customer& lhs, const Customer& rhs) { return lhs.name == rhs.name; }