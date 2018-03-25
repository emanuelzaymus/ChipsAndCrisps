#include "structures\heap_monitor.h"

#include <cstdlib>
#include <ctime>

#include "SupplierGoods.h"


void SupplierGoods::generateAmountAndPrice()
{
	amount = rand() % (type.maxAmount + 1);
	currentPrice = (double)rand() / RAND_MAX;// *maxPrice + 1;
	currentPrice = currentPrice * (type.maxPrice - 1) + 1;
}

SupplierGoods::SupplierGoods(GoodsType type)
	: Goods(type)
{
	generateAmountAndPrice();
}

SupplierGoods::~SupplierGoods()
{
}

Goods SupplierGoods::sell()
{
	transaction30.add({ currentPrice, time(NULL) });
	Goods ret = Goods(type, amount);
	update();
	generateAmountAndPrice();
	return ret;
}

//IS NOT TESTED !!!!!!!!!!!!!!
void SupplierGoods::update()
{
	if (transaction30.isEmpty())
	{
		return;
	}
	while (transaction30[0].date - time(NULL) > (60 * 60 * 24 * 30))
	{
		transaction30.removeAt(0);
	}
	averagePrice30 = 0;
	for (Transaction t : transaction30)
	{
		averagePrice30 += t.price;
	}
	averagePrice30 /= transaction30.size();
	//averagePrice30 = (priceWeight * averagePrice30 + currentPrice) / (priceWeight + 1);
	//priceWeight++;
}
