#include "structures\heap_monitor.h"

#include <cstdlib>
#include <ctime>

#include "SupplierGoods.h"
#include "Manager.h"


void SupplierGoods::generateAmountAndPrice()
{
	amount = rand() % (type.maxAmount + 1);
	currentUnitPrice = (double)rand() / RAND_MAX;
	currentUnitPrice = currentUnitPrice * (type.maxUnitPrice - 1) + 1;
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
	transaction30.add({ currentUnitPrice, Manager::TODAY, amount });
	Goods ret = Goods(type, amount);
	update();

	generateAmountAndPrice();
	return ret;
}

void SupplierGoods::update()
{
	if (transaction30.isEmpty()) {
		return;
	}
	while (transaction30[0].date - Manager::TODAY > (30 * Manager::DAY_SEC)) {
		transaction30.removeAt(0);
	}
	averagePrice30 = 0;
	costs30 = 0;
	boughtAmount30 = 0;
	for (Transaction t : transaction30)
	{
		averagePrice30 += t.price;
		costs30 += t.price * t.amount;
		boughtAmount30 += t.amount;
	}
	averagePrice30 /= transaction30.size();
}
