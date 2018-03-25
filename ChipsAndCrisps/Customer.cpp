#include "structures\heap_monitor.h"

#include <cstdlib>

#include "Customer.h"


Customer::Customer(std::string name, int address)
	:BusinessPartner(name), address(address)
{
	waitingOrders = new structures::ExplicitQueue<Order*>();
}

Customer::~Customer()
{
	while (!waitingOrders->isEmpty())
		delete waitingOrders->pop();
	delete waitingOrders;
}

void Customer::createOrder()
{
	ProductName name;
	if (rand() % 2)
		name = ProductName::chips;
	else
		name = ProductName::crisps;
	
	waitingOrders->push(new Order(*this, Product(name, rand() % 1900 + 100), ((double)rand() / RAND_MAX) * 3.5 + 3, time(NULL), time(NULL)/*todo delivery deathline*/));
}
