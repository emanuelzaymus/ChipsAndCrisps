#include "structures\heap_monitor.h"

#include "Order.h"



Order::Order()
{
}


Order::~Order()
{
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