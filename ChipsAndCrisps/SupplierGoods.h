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
		double amount;
		bool operator== (const Transaction& tran) const { return price == tran.price && date == tran.date && amount == tran.amount; }
	};

	double currentUnitPrice = 0;
	double averagePrice30 = 0;
	double costs30 = 0;
	int boughtAmount30 = 0;
	structures::LinkedList<Transaction> transaction30;

	void generateAmountAndPrice();
	void update();
public:

	SupplierGoods(GoodsType type);
	~SupplierGoods();

	Goods sell();

	double getCurrentUnitPrice() { return currentUnitPrice; }
	double getTotalPrice() { return currentUnitPrice * amount; }

	int getRoundedAveragePrice30() { return (int)averagePrice30; }
	double getAveragePrice30() { return averagePrice30; }
	double getCosts30() { return costs30; }
	int getBoughtAmount30() { return boughtAmount30; }

	friend std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj);
};

inline std::ostream& operator<<(std::ostream &strm, const SupplierGoods &obj) {
	char avgPrice[10];
	sprintf(avgPrice, "%1.2f", obj.averagePrice30);
	return strm << obj.type.formattedName << " (" << avgPrice << ")  ";
}