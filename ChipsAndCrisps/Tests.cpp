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


#include "Tests.h"
#include "Goods.h"
#include "Supplier.h"
#include "Vehicle.h"
#include "Customer.h"
#include "Manager.h"


structures::ArrayList<Supplier*>* Tests::generateSuppliers()
{
	structures::ArrayList<Supplier*> *ret = new structures::ArrayList<Supplier*>();

	return ret;
}

Tests::Tests()
{
}


Tests::~Tests()
{
}

bool Tests::test()
{
	Manager man("Chips And Crisps");

	structures::ArrayList<SupplierGoods*> *a = new structures::ArrayList<SupplierGoods*>();
	SupplierGoods *s = new SupplierGoods(Goods::oil);
	SupplierGoods *s2 = new SupplierGoods(Goods::flavouring);
	SupplierGoods *s3 = new SupplierGoods(Goods::potatoes);

	a->add(s);
	a->add(s2);
	a->add(s3);


	return true;
}
