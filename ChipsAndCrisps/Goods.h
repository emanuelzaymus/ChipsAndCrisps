#pragma once

#include <string>

#include "structures\heap_monitor.h"


//enum GoodsName { potatoes, oil,flavouring };

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
	int amount;

public:
	static const GoodsType potatoes;	//kg
	static const GoodsType oil;			//l
	static const GoodsType flavouring;	//g

	Goods(GoodsType type);
	Goods(GoodsType type, double amount);
	~Goods();

	GoodsType getType() { return type; }

	friend bool operator==(const Goods& lhs, const Goods& rhs);
};

inline bool operator==(const Goods& lhs, const Goods& rhs) { return lhs.type == rhs.type && lhs.amount == rhs.amount; }