#include "structures\heap_monitor.h"

#include <cstdlib>

#include "Customer.h"
#include "Product.h"
#include "Order.h"
#include "Manager.h"



int Customer::getWeight(structures::LinkedList<Order&> &ords)
{
	int weight(0);
	for each (Order& ord in ords)
	{
		weight += ord.getProduct().getAmount();
	}
	return weight;
}

double Customer::getPrice(structures::LinkedList<Order&>& ords)
{
	double price(0);
	for each (Order& ord in ords)
	{
		price += ord.getTotalPrice();
	}
	return price;
}

Customer::Customer(std::string name, int address)
	:BusinessPartner(name), address(address)
{
	orders = new structures::LinkedList<Order*>();
}


Customer::~Customer()
{
	while (!orders->isEmpty())
		delete orders->removeAt(0);
	delete orders;
}

void Customer::createOrder(time_t deliveryDeathLine)
{
	ProductName name;
	if (rand() % 2)
		name = ProductName::chips;
	else
		name = ProductName::crisps;

	Order *newOrder = new Order(this, Product(name, rand() % 50 + 100),((double)rand() / RAND_MAX) * 3.5 + 15, deliveryDeathLine);
	addOrder(newOrder);
}

void Customer::addOrder(Order * newOrder)
{
	orders->add(newOrder);
	waitingOrders.push(*newOrder);
	newOrder->setCustomer(this);
}

void Customer::addGoodOrder(Order & good)
{
	goodOrders.add(good);
	incomeFromCustomer += good.getTotalPrice();
}

double Customer::getIncomeFromTo(time_t fromDay, time_t toDay)
{
	double income(0);

	struct tm * dayInfo;
	dayInfo = localtime(&fromDay);
	int from_year = dayInfo->tm_year;
	int from_yday = dayInfo->tm_yday;
	dayInfo = localtime(&toDay);
	int to_year = dayInfo->tm_year;
	int to_yday = dayInfo->tm_yday;

	time_t deliveryDate;
	for (Order &ord : goodOrders)
	{
		deliveryDate = ord.getDeliveryDate();
		dayInfo = localtime(&deliveryDate);
		if (from_year <= dayInfo->tm_year && from_yday <= dayInfo->tm_yday && to_year >= dayInfo->tm_year && to_yday >= dayInfo->tm_yday)
		{
			income += ord.getTotalPrice();
		}
	}
	return income;
}

std::string Customer::about(time_t fromDay = Manager::TODAY - 365 * Manager::DAY_SEC, time_t toDay = Manager::TODAY)
{
	char income[10];
	sprintf(income, "%4.2f", getIncomeFromTo(fromDay, toDay));
	char cancelledWeight[10];
	sprintf(cancelledWeight, "%4d", getWeight(cancelledOrders));
	char cancelledPrice[10];
	sprintf(cancelledPrice, "%4.2f", getPrice(cancelledOrders));
	char rejectedWeight[10];
	sprintf(rejectedWeight, "%4d", getWeight(rejectedOrders));
	char rejectedPrice[10];
	sprintf(rejectedPrice, "%4.2f", getPrice(rejectedOrders));

	std::string aboutString;
	aboutString += formattedName + "  (" + std::to_string(address) + ")  income: " + income + " EUR"
		+ "\n    Canceled orders: count = " + std::to_string(cancelledOrders.size()) + "  weight = " + cancelledWeight + " kg  price = " + cancelledPrice + " EUR"
		+ "\n    Rejcted orders:  count = " + std::to_string(rejectedOrders.size()) + "  weight = " + rejectedWeight + " kg  price = " + rejectedPrice + " EUR"
		;

	return aboutString;
}
