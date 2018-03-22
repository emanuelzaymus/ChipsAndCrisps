#pragma once

#include "structures\heap_monitor.h"

#include "Goods.h"

class SupplierGoods :
	public Goods
{
private:
	int currentPrice;
	int averagePrice = 0;
	int totalCosts = 0;
	int totalBoughtAmount = 0;
	int importance = 1;

	void generateAmountAndPrice();

public:

	SupplierGoods(GoodsType type);
	~SupplierGoods();

	void update();

	friend std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj) {
	return strm << obj.type.name << " (" << obj.averagePrice << ")  ";
}