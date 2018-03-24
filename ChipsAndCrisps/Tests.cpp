#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>

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


bool Tests::testSupplier()
{
	generateSuppliers();

	structures::LinkedList<Supplier&>& sups = manager->getSuppliers();
	for (Supplier &s : sups) {
		std::cout << s << std::endl;
	}

	std::cout << std::endl << "Suppliers of " << Goods::potatoes.name << std::endl;
	structures::LinkedList<Supplier&>& psups = manager->getSuppliers(Goods::potatoes);
	for (Supplier &s : psups) {
		std::cout << s << std::endl;
	}
	std::cout << std::endl << "Suppliers of " << Goods::oil.name << std::endl;
	structures::LinkedList<Supplier&>& osups = manager->getSuppliers(Goods::oil);
	for (Supplier &s : osups) {
		std::cout << s << std::endl;
	}
	std::cout << std::endl << "Suppliers of " << Goods::flavouring.name << std::endl;
	structures::LinkedList<Supplier&>& fsups = manager->getSuppliers(Goods::flavouring);
	for (Supplier &s : fsups) {
		std::cout << s << std::endl;
	}
	return true;
}

void Tests::generateSuppliers()
{
	int countOfSuppliers = rand() % 15 + 10;
	for (size_t i = 0; i < countOfSuppliers; i++)
	{
		structures::ArrayList<SupplierGoods*> *suppliersGoods = generateSuppliersGoods();
		Supplier *supplier = new Supplier(randName(), *suppliersGoods);
		manager->addSupplier(*supplier);
	}
}

structures::ArrayList<SupplierGoods*> * Tests::generateSuppliersGoods()
{
	structures::ArrayList<SupplierGoods*> * suppliersGoods = new structures::ArrayList<SupplierGoods*>();
	for (size_t i = 0; i < 3; i++)
	{
		if ((rand() % 2) == 0)
			continue;

		GoodsType type;
		switch (i + 1)
		{
		case 1:
			type = Goods::potatoes;
			break;
		case 2:
			type = Goods::oil;
			break;
		case 3:
			type = Goods::flavouring;
			break;
		}
		SupplierGoods *goods = new SupplierGoods(type);
		suppliersGoods->add(goods);
	}
	return suppliersGoods;
}

std::string Tests::randName()
{
	int count = rand() % 10 + 3;
	std::string name = "";
	name += char(rand() % 25 + 65);
	for (size_t i = 0; i < count; i++)
	{
		name += char(rand() % 25 + 97);
	}
	return name;
}

Tests::Tests()
{
	manager = new Manager("Chips And Crisps");
}


Tests::~Tests()
{
	structures::LinkedList<Supplier&>& sup = manager->getSuppliers();
	while (!sup.isEmpty())
	{
		Supplier s =sup.removeAt(0);
		structures::ArrayList<SupplierGoods*>& g= s.getGoods();
		while (!g.isEmpty())
		{
			//delete 
				g.removeAt(g.size() - 1);
		}
		//delete &s;
	}
	//delete &sup;

	delete manager;
}

bool Tests::test()
{

	bool supplier = testSupplier();

	//structures::ArrayList<SupplierGoods*> *a = new structures::ArrayList<SupplierGoods*>();
	//SupplierGoods *s = new SupplierGoods(Goods::oil);
	//SupplierGoods *s2 = new SupplierGoods(Goods::flavouring);
	//SupplierGoods *s3 = new SupplierGoods(Goods::potatoes);

	//a->add(s);
	//a->add(s2);
	//a->add(s3);


	//Supplier *sup = new Supplier("First", *a);
	//Supplier *sup2 = new Supplier("Firsa", *a);
	//Supplier *sup3 = new Supplier("DDDD", *a);
	//Supplier *sup4 = new Supplier("AAbb", *a);
	//Supplier *sup5 = new Supplier("bb", *a);
	//Supplier *sup6 = new Supplier("AAAA", *a);


	//manager->addSupplier(*sup);
	//manager->addSupplier(*sup2);
	//manager->addSupplier(*sup3);
	//manager->addSupplier(*sup4);
	//manager->addSupplier(*sup5);
	//manager->addSupplier(*sup6);

	//structures::LinkedList<Supplier&> suppliers = manager->getSuppliers();
	//for (Supplier s : suppliers) {
	//	std::cout << s << std::endl;
	//}

	//std::cout << std::endl;


	//for (Supplier s : suppliers) {
	//	std::cout << s << std::endl;
	//}

	//std::cout << "potatoes" << std::endl;
	//structures::LinkedList<Supplier&> potatoesSuppliers = manager->getSuppliers(Goods::flavouring);
	//for (Supplier s : potatoesSuppliers) {
	//	std::cout << s << std::endl;
	//}


	//delete sup;
	//delete sup2;
	//delete sup3;
	//delete sup4;
	//delete sup5;
	//delete sup6;

	//delete a;
	//delete s;
	//delete s2;
	//delete s3;


	return true;
}
