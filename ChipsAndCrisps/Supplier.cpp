#include "structures\heap_monitor.h"

#include "Supplier.h"


Supplier::Supplier(std::string name, structures::ArrayList<SupplierGoods*> *goods)
	: BusinessPartner(name), goods(goods)
{
}

Supplier::~Supplier()
{
	while (!goods->isEmpty())
		delete goods->removeAt(goods->size() - 1);
	delete goods;
}

SupplierGoods & Supplier::getGoods(GoodsType type)
{
	for (SupplierGoods *g : *goods) {
		if (g->getType() == type)
		{
			return *g;
		}
	}
}

//todo unnecessary
bool Supplier::has(GoodsType type)
{
	for (SupplierGoods *g : *goods)
		if (g->getType() == type)
		{
			return true;
		}
	return false;
}

Goods Supplier::buy(GoodsType type)
{
	return getGoods(type).sell();
}

std::string Supplier::aboutBest(GoodsType type)
{
	SupplierGoods& goods = getGoods(type);
	char totalCost[10];
	sprintf(totalCost, "%4.2f", goods.getCosts30());
	char avgPrice[10];
	sprintf(avgPrice, "%4.2f", goods.getAveragePrice30());

	std::string about;
	about += formattedName + "  bought amount = " + std::to_string(goods.getBoughtAmount30())
		+ " kg  total price = " + totalCost 
		+ " EUR  average price = " + avgPrice + " EUR/kg";
	return about;
}


