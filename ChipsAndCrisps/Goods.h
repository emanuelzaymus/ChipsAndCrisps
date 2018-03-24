#pragma once

#include <string>

#include "structures\heap_monitor.h"


//enum GoodsName { potatoes, oil,flavouring };

struct GoodsType
{
	std::string name;
	std::string formatedName;
	int code;

	bool operator== (const GoodsType& spec) const { return name == spec.name; }
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