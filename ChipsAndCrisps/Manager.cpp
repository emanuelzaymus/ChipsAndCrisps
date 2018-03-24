#include "structures\heap_monitor.h"

#include <string>
#include <algorithm>

#include "Manager.h"



void Manager::addAlphabetical(structures::LinkedList<Supplier&> &list, Supplier &supplier)
{
	int index = 0;
	std::string newName = supplier.getName();
	std::transform(newName.begin(), newName.end(), newName.begin(), ::tolower);
	std::string existingName;
	for (Supplier s : list)
	{
		existingName = s.getName();
		std::transform(existingName.begin(), existingName.end(), existingName.begin(), ::tolower);
		if (newName.compare(existingName) <= 0)
		{
			break;
		}
		index++;
	}
	list.insert(supplier, index);
}

void Manager::sortByGoods(Supplier & supplier)
{
	for (SupplierGoods *g : supplier.getGoods()) {
		switch (g->getType().code)
		{
		case 1:
			addAlphabetical(potatoesSups, supplier);
			priorityPotatoesSups.push(g->getAveragePrice(), supplier);
			break;
		case 2:
			addAlphabetical(oilSups, supplier);
			priorityOilSups.push(g->getAveragePrice(), supplier);
			break;
		case 3:
			addAlphabetical(flavouringSups, supplier);
			priorityFlavouringSups.push(g->getAveragePrice(), supplier);
			break;
		}
	}
}

Manager::Manager(std::string companyName) : companyName(companyName)
{
	delete suppliers;
}

Manager::~Manager()
{
	//if (&suppliers != nullptr)
	//{
	//	while (!suppliers.isEmpty())
	//	{
	//		delete &suppliers.removeAt(0);
	//	}
	//}
}

void Manager::addSupplier(Supplier & supplier)
{
	addAlphabetical(*suppliers, supplier);
	sortByGoods(supplier);
}

structures::LinkedList<Supplier&>& Manager::getSuppliers(GoodsType type)
{
	switch (type.code)
	{
	case 1:
		return potatoesSups;
	case 2:
		return oilSups;
	case 3:
		return flavouringSups;
	}
}
