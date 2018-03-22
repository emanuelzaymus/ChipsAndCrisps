#include "structures\heap_monitor.h"

#include "SupplierGoods.h"





void SupplierGoods::generateAmountAndPrice()
{
	//todo random values
	amount = 100;
	currentPrice = 30;
	update();
}

SupplierGoods::SupplierGoods(GoodsType type)
	: Goods(type)
{
	generateAmountAndPrice();
}

SupplierGoods::~SupplierGoods()
{
	
}

void SupplierGoods::update()
{
	//averagePrice = 
}
