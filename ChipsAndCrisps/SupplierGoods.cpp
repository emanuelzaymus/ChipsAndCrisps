#include "structures\heap_monitor.h"

#include <cstdlib>
#include <ctime>

#include "SupplierGoods.h"


void SupplierGoods::generateAmountAndPrice()
{
	update();
	amount = rand() % (maxAmount + 1);
	currentPrice = (double)rand() / RAND_MAX;// *maxPrice + 1;
	currentPrice = currentPrice * (maxPrice - 1) + 1;
}

SupplierGoods::SupplierGoods(GoodsType type)
	: Goods(type)
{
	switch (type.code)
	{
	case 1:
		maxAmount = 5000;
		maxPrice = 3;
		break;
	case 2:
		maxAmount = 1000;
		maxPrice = 4;
		break;
	case 3:
		maxAmount = 50000;
		maxPrice = 2;
		break;
	}
	generateAmountAndPrice();
}

SupplierGoods::~SupplierGoods()
{
}

void SupplierGoods::update()
{
	averagePrice = (priceWeight * averagePrice + currentPrice) / (priceWeight + 1);
	priceWeight++;
}
