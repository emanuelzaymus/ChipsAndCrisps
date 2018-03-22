#pragma once

#include <string>

#include "structures\heap_monitor.h"


//enum GoodsName { potatoes, oil,flavouring };

struct GoodsType
{
	std::string name;
};

class Goods
{
protected:
	GoodsType type;
	double amount;

public:
	static const GoodsType potatoes;
	static const GoodsType oil;
	static const GoodsType flavouring;

	Goods(GoodsType type);
	Goods(GoodsType type, double amount);
	~Goods();

	GoodsType getType() { return type; }

	friend bool operator==(const Goods& lhs, const Goods& rhs);
};

inline bool operator==(const Goods& lhs, const Goods& rhs) { return lhs.type == rhs.type && lhs.amount == rhs.amount; }