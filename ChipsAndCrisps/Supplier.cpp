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
bool Supplier::has(GoodsType name)
{
	for (SupplierGoods *g : *goods)
		if (g->getType() == name)
		{
			return true;
		}
	return false;
}
