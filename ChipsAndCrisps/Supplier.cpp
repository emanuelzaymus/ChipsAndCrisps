#include "structures\heap_monitor.h"

#include "Supplier.h"


Supplier::Supplier(std::string name, structures::ArrayList<SupplierGoods*> &goods)
	: name(name), goods(goods)
{
	//goods = new structures::ArrayList<SupplierGoods*>();
}

Supplier::~Supplier()
{
	//if (&goods != nullptr)
	//{
	//	while (!goods.isEmpty())
	//	{
	//		delete goods.removeAt(goods.size() - 1);
	//	}
	//	delete &goods;
	//}
}

//todo unnecessary
bool Supplier::has(GoodsType name)
{
	for (SupplierGoods *g : goods)
		if (g->getType() == name)
		{
			return true;
		}
	return false;
}
