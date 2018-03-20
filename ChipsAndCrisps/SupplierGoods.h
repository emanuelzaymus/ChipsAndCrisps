#pragma once
#include "Goods.h"
class SupplierGoods :
	public Goods
{
private:
	int averagePrice;
	int currentPrice;
	int totalCosts;
	int totalBoughtAmount;

	void generateAmountAndPrice();

public:

	SupplierGoods(GoodsName name, int amount);
	~SupplierGoods();

	void update();
};

