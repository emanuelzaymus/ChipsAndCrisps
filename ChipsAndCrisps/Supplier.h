#pragma once

#include <string>
#include <ostream>

#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"

#include "BusinessPartner.h"
#include "SupplierGoods.h"


class Supplier : public BusinessPartner
{
private:
	structures::ArrayList<SupplierGoods*> *goods;

public:
	Supplier(std::string name, structures::ArrayList<SupplierGoods*> *goods);
	~Supplier();

	structures::ArrayList<SupplierGoods*> & getGoods() { return *goods; }
	SupplierGoods & getGoods(GoodsType type);
	bool has(GoodsType type);
	Goods buy(GoodsType type);

	friend std::ostream& operator<<(std::ostream &strm, const Supplier &obj);
	friend bool operator==(const Supplier& lhs, const Supplier& rhs);
};


inline std::ostream& operator<<(std::ostream &strm, const Supplier &obj) {
	strm << obj.getFormattedName() << " - ";
	for (SupplierGoods *g : *obj.goods) {
		strm << *g;
	}
	return strm;
}

inline bool operator==(const Supplier& lhs, const Supplier& rhs) { return lhs.name == rhs.name; }