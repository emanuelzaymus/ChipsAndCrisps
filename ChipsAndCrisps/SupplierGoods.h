#pragma once

#include <ctime>

#include "structures\heap_monitor.h"
#include "structures\list\linked_list.h"

#include "Goods.h"

class SupplierGoods : public Goods
{
private:
	struct Transaction
	{
		double price;
		time_t date;
		bool operator== (const Transaction& tran) const { return price == tran.price && date == tran.date; }
	};

	double currentPrice = 0;
	double averagePrice30 = 0;
	double totalCosts = 0;
	int totalBoughtAmount = 0;
	structures::LinkedList<Transaction> transaction30;

	void generateAmountAndPrice();
	void update();
public:

	SupplierGoods(GoodsType type);
	~SupplierGoods();

	Goods sell();

	int getRoundedAveragePrice() { return (int)averagePrice30; }
	double getAveragePrice() { return averagePrice30; }

	friend std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj) {
	return strm << obj.type.formattedName << " (" << obj.averagePrice30 << ")  ";
}