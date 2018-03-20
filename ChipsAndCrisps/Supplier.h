#pragma once

#include <string>
#include <ostream>

#include "SupplierGoods.h"

class Supplier
{
private:
	std::string name;

	//SupplierGoods goods[];

public:
	Supplier(std::string name);
	~Supplier();

	std::string getName() { return name; }

	friend std::ostream& operator<<(std::ostream &strm, const Supplier &obj);
};


inline std::ostream& operator<<(std::ostream &strm, const Supplier &obj) {
	return strm << obj.name;
}
