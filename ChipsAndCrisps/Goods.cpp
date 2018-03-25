#include "structures\heap_monitor.h"

#include "Goods.h"


const GoodsType Goods::potatoes = { "Potatoes", "Potatoes  ", 1, 5000, 3 };
const GoodsType Goods::oil = { "Oil", "Oil       ", 2, 1000, 4 };
const GoodsType Goods::flavouring = { "Flavouring", "Flavouring", 3, 50000, 2 };

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
