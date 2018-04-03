#pragma once

#include "structures\heap_monitor.h"

#include "Goods.h"

enum ProductName { chips, crisps };

static const Goods CHIPS_INGREDIENTS[2] = { Goods(Goods::potatoes, 1.5),  Goods(Goods::oil, 0.2) };
static const Goods CRISPS_INGREDIENTS[3] = { Goods(Goods::potatoes, 2),  Goods(Goods::oil, 0.4), Goods(Goods::flavouring, 0.02) };

class Product
{
private:
	int amount;
	ProductName name;
	std::string strName;

public:
	Product(ProductName name, int amount);
	Product();
	~Product();

	int getAmount() const { return amount; }
	void setAmount(int newAmount) { amount = newAmount; }
	ProductName getName() const { return name; }
	std::string getStrName() const { return strName; }

	void setName(ProductName n) { name = n; }

	friend bool operator==(const Product& lhs, const Product& rhs);
};

inline bool operator==(const Product& lhs, const Product& rhs) { return lhs.name == rhs.name && lhs.amount == rhs.amount; }
