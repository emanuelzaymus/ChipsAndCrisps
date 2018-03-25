#include "structures\heap_monitor.h"

#include "Product.h"



Product::Product(ProductName name, int amount)
	: name(name), amount(amount), strName(name == ProductName::chips ? "Chips " : "Crisps")
{
}

Product::~Product()
{
}
