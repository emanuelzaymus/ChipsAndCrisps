#include "structures\heap_monitor.h"

#include "Order.h"
#include "Customer.h"




Order::Order(Customer & customer, Product product, double price, time_t recordDate, time_t deliveryDeathLine)
	: customer(customer), product(product), price(price), recordDate(recordDate), deliveryDeathLine(deliveryDeathLine)
{
}

Order::~Order()
{
	//delete product;
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