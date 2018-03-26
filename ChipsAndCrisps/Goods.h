#pragma once

#include <string>

#include "structures\heap_monitor.h"



struct GoodsType
{
	std::string name;
	std::string formattedName;
	int code;
	int maxAmount;
	double maxPrice;

	bool operator== (const GoodsType& type) const { return name == type.name; }
};

class Goods
{
protected:
	GoodsType type;
	double amount;

public:
	static const GoodsType potatoes;	//kg
	static const GoodsType oil;			//l
	static const GoodsType flavouring;	//g

	Goods(GoodsType type);
	Goods(GoodsType type, double amount);
	~Goods();

	GoodsType getType() { return type; }
	double getAmount() const { return amount; }
	void addAmount(double a) { amount += a; }
	double clear();

	friend bool operator==(const Goods& lhs, const Goods& rhs);
};

inline bool operator==(const Goods& lhs, const Goods& rhs) { return lhs.type == rhs.type && lhs.amount == rhs.amount; }