#pragma once

#include <string>

#include "structures\heap_monitor.h"

//#include "Order.h"


class BusinessPartner
{
protected:
	std::string name;

public:
	BusinessPartner(std::string name);
	~BusinessPartner();

	std::string getName() { return name; }
};

