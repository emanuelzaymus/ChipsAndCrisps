#include "structures\heap_monitor.h"

#include "Goods.h"


const GoodsType Goods::potatoes = { "Potatoes","Potatoes  ", 1 };
const GoodsType Goods::oil = { "Oil","Oil       ", 2 };
const GoodsType Goods::flavouring = { "Flavouring","Flavouring", 3 };

Goods::Goods(GoodsType type) : type(type)
{
}

Goods::Goods(GoodsType type, double amount)
	: type(type), amount(amount)
{
}

Goods::~Goods()
{
}
