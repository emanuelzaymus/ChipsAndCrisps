#include "structures\heap_monitor.h"

#include <cstdlib>

#include "Customer.h"
#include "Product.h"
#include "Order.h"


Customer::Customer(std::string name, int address)
	:BusinessPartner(name), address(address)
{
	orders = new structures::LinkedList<Order*>();
}

Customer::~Customer()
{
	while (!orders->isEmpty())
		delete orders->removeAt(0);
	delete orders;
}

void Customer::createOrder(time_t deliveryDeathLine)
{
	ProductName name;
	if (rand() % 2)
		name = ProductName::chips;
	else
		name = ProductName::crisps;
	
	Order *newOrder = new Order(*this, Product(name, rand() % 1900 + 100), ((double)rand() / RAND_MAX) * 3.5 + 3, /*time(NULL),*/ deliveryDeathLine);
	orders->add(newOrder);
	waitingOrders.push(*newOrder);
}
