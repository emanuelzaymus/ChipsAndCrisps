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


#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"
#include "Tests.h"

int main() {
	initHeapMonitor();

	Tests tests;
	if (!tests.test())
	{
		return 1;
	}



	Manager m("Chips And Crisps");

	structures::ArrayList<SupplierGoods*> *a = new structures::ArrayList<SupplierGoods*>();
	SupplierGoods *s = new SupplierGoods(Goods::oil);
	SupplierGoods *s2 = new SupplierGoods(Goods::flavouring);
	SupplierGoods *s3 = new SupplierGoods(Goods::potatoes);

	a->add(s);
	a->add(s2);
	a->add(s3);

	Supplier *sup = new Supplier("First", *a);


	m.addSupplier(*sup);

	structures::LinkedList<Supplier> suppliers = m.getSuppliers();
	for (Supplier s : suppliers) {
		std::cout << s << std::endl;
	}

	delete sup;
	
	delete a;
	delete s;
	delete s2;
	delete s3;
	



	//fflavouring.name = "sd";

	//std::time_t t = std::time(0);   // get time now
	//std::tm* now = std::localtime(&t);
	//std::cout << (now->tm_year + 1900) << '-'
	//	<< (now->tm_mon + 1) << '-'
	//	<< now->tm_mday
	//	<< "\n";


	//time_t teraz = time(NULL);
	//
	//time_t rawtime;

	//time(&rawtime);
	//printf("The current local time is: %s", ctime(&rawtime));



	return 0;
}