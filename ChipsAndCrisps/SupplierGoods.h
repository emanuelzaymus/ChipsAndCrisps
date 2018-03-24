#pragma once

#include "structures\heap_monitor.h"

#include "Goods.h"

class SupplierGoods :
	public Goods
{
private:
	double currentPrice = 0;
	double averagePrice = 0;
	double totalCosts = 0;
	int totalBoughtAmount = 0;
	int priceWeight = 1;

	int maxAmount;
	int maxPrice;

	void generateAmountAndPrice();

public:

	SupplierGoods(GoodsType type);
	~SupplierGoods();

	int getRoundedAveragePrice() { return (int)averagePrice; }
	double getAveragePrice() { return averagePrice; }
	void update();

	friend std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj) {
	return strm << obj.type.formatedName << " (" << obj.averagePrice << ")  ";
}