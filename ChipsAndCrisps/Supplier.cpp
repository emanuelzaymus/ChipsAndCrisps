#include "structures\heap_monitor.h"

#include "Supplier.h"






Supplier::Supplier(std::string name, structures::ArrayList<SupplierGoods*> &goods)
	: name(name), goods(goods)
{
}

Supplier::~Supplier()
{
}

bool Supplier::has(GoodsType name)
{
	for(SupplierGoods* g : goods)
		if (g->getType() == name)
		{
			return true;
		}
	return false;
}
