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


#include "Order.h"
#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"
#include "Tests.h"

int main() {
	initHeapMonitor();

	srand(time(NULL));

	Tests tests;
	if (!tests.test())
	{
		return 1;
	}





	//fflavouring.name = "sd";

	//std::time_t t = std::time(0);   // get time now
	//std::tm* now = std::localtime(&t);
	//std::cout << (now->tm_year + 1900) << '-'
	//	<< (now->tm_mon + 1) << '-'
	//	<< now->tm_mday
	//	<< "\n";


	//time_t teraz = time(NULL);

	//teraz += Manager::DAY_SEC *3;

	//char buffer[30];
	//sprintf(buffer, "%s", ctime(&teraz));
	//std::cout << buffer << std::endl;
	////printf("%s", buffer);

	//std::string aaa = std::string(buffer);





	//time_t rawtime;

	//time(&rawtime);
	//std::string cas = sprintf("The current local time is: %s", ctime(&teraz));




	return 0;
}