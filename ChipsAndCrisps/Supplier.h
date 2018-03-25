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
	bool has(GoodsType name);

	friend std::ostream& operator<<(std::ostream &strm, const Supplier &obj);
	friend bool operator==(const Supplier& lhs, const Supplier& rhs);
};


inline std::ostream& operator<<(std::ostream &strm, const Supplier &obj) {
	std::string formattedName = obj.name;
	for (size_t i = 0; i < 15 - obj.name.length(); i++)
		formattedName += ' ';

	strm << formattedName << " - ";
	for (SupplierGoods *g : *obj.goods) {
		strm << *g;
	}
	return strm;
}

inline bool operator==(const Supplier& lhs, const Supplier& rhs) { return lhs.name == rhs.name; }