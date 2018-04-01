#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

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

	return 0;
}