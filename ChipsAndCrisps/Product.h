#pragma once

#include "Goods.h"

enum ProductName { chips, crisps };

static const Goods CHIPS_INGREDIENTS[2] = { Goods(GoodsName::potatoes, 2),  Goods(GoodsName::oil, 0.4) };
static const Goods CRISPS_INGREDIENTS[3] = { Goods(GoodsName::potatoes, 1.5),  Goods(GoodsName::oil, 0.2), Goods(GoodsName::flavouring, 0.02) };

class Product
{
private:
	int amount;
	ProductName name;

public:

	Product(ProductName name, int amount);
	~Product();
};

