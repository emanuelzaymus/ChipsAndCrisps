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

int main() {
	initHeapMonitor();

	srand(time(NULL));
	
	Tests tests;
	if (!tests.test())
	{
		return 1;
	}
	




	/*
	structures::Heap<char> asdf;

	asdf.push(5, 'A');
	asdf.push(6, 'B');
	asdf.push(9, 'C');
	asdf.push(1, 'D');
	asdf.push(0, 'E');
	asdf.push(15, 'F');
	asdf.push(-5, 'G');
	asdf.push(7, 'H');
	asdf.push(4, 'I');

	while (!asdf.isEmpty())
	{
		int prior = asdf.peekPriority();
		std::cout << prior << " - " << asdf.pop() << std::endl;
	}
	*/


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