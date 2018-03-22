#include "structures\heap_monitor.h"

#include "Goods.h"


const GoodsType Goods::potatoes = { "Potatoes" };
const GoodsType Goods::oil = { "Oil" };
const GoodsType Goods::flavouring = { "Flavouring" };

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
