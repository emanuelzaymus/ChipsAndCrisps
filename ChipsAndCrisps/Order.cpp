#include "structures\heap_monitor.h"

#include "Order.h"
#include "Customer.h"




Order::Order(Customer & customer, Product product, double price, time_t deliveryDeathLine)
	: customer(customer), product(product), price(price), deliveryDeathLine(deliveryDeathLine)
{
}

Order::~Order()
{
}

void Order::setRejected()
{
	rejected = true;
	customer.addRejectedOrder(*this);
}

void Order::cancel()
{
	cancelled = true;
	customer.addCancelledOrder(*this);
}

bool operator==(const Order& lhs, const Order& rhs)
{
	return lhs.cancelled == rhs.cancelled
		&& lhs.deliveryDate == rhs.deliveryDate
		&& lhs.deliveryDeathLine == rhs.deliveryDeathLine
		&& lhs.done == rhs.done
		&& lhs.price == rhs.price
		&& lhs.product == rhs.product
		&& lhs.recordDate == rhs.recordDate
		&& lhs.rejected == rhs.rejected;
}