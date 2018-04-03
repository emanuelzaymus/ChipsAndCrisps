#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <fstream>

#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"
#include "structures\list\linked_list.h"
#include "structures\array\array.h"
#include "structures\stack\explicit_stack.h"
#include "structures\priority_queue\priority_queue_unsorted_array_list.h"
#include "structures\priority_queue\heap.h"


#include "Order.h"
#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"
#include "Tests.h"
#include "CLI.h"

int main() {
	initHeapMonitor();

	srand(time(NULL));

	CLI cli;

	cli.run();

	//Customer *c = new Customer("Emanuel", 8);
	//Order *savedOrder = new Order(c, Product(ProductName::crisps, 10), 2.54, time(NULL));
	//c->addOrder(savedOrder);
	//savedOrder->save("order_file.txt");


	//Order * loadedOrder = new Order("order_file.txt");
	//c->addOrder(loadedOrder);


	//delete c;


	return 0;
}