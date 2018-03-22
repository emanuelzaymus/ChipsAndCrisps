#include "structures\heap_monitor.h"

#include "Manager.h"



Manager::Manager(std::string companyName) : companyName(companyName)
{
}

Manager::~Manager()
{
}

void Manager::addSupplier(Supplier & supplier)
{
	suppliers.add(supplier);//prerob na linked list, ukladaj v abecednom poradi
	// zatried do dalsich (podla vyrobkov) listov abecedne 

	//spolocny zoznam arraylist vetci abecedne
	//abecedne zoznamy -arraylist (pre kazdy vyrobok)
	//prioritny from pre kazdy VYROK
}

structures::LinkedList<Supplier>& Manager::getSuppliers(GoodsType name)
{
	structures::LinkedList<Supplier> choosen;
	for (Supplier s : suppliers)
	{
		if (s.has(name))
		{
			choosen.add(s);
		}
	}
	return choosen;
}
