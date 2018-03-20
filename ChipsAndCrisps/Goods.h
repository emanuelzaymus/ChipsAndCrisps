#pragma once

enum GoodsName { potatoes, oil, flavouring };

class Goods
{
private:
	GoodsName name;
	double amount;

public:
	Goods(GoodsName name, double amount);
	~Goods();
};

