#include <fstream>
#include <iostream>

#include "structures\heap_monitor.h"

#include "Order.h"
#include "Customer.h"
#include "Manager.h"




Order::Order(Customer * customer, Product product, double unitPrice, time_t deliveryDeathLine)
	: customer(customer), product(product), unitPrice(unitPrice), deliveryDeathLine(deliveryDeathLine)
{
}

Order::Order(std::string path)
{
	Product p;
	product = p;

	std::string line;
	std::ifstream file(path);
	if (file.is_open())
	{
		getline(file, line);
		std::cout << line << "\n";
		std::string productName = line;
		product.setName(productName == "0" ? ProductName::chips : ProductName::crisps);

		getline(file, line);
		std::cout << line << "\n";
		int amount = std::stoi(line);
		product.setAmount(amount);

		std::string::size_type sz;
		getline(file, line);
		std::cout << line << "\n";
		unitPrice = std::stod(line, &sz);

		getline(file, line);
		std::cout << line << "\n";
		recordDate = std::stoll(line, &sz);

		getline(file, line);
		std::cout << line << "\n";
		deliveryDeathLine = std::stoll(line, &sz);

		getline(file, line);
		std::cout << line << "\n";
		deliveryDate = std::stoi(line);

		getline(file, line);
		std::cout << line << "\n";
		done = std::stoi(line);
		
		getline(file, line);
		std::cout << line << "\n";
		cancelled = std::stoi(line);

		getline(file, line);
		std::cout << line << "\n";
		rejected = std::stoi(line);

		getline(file, line);
		std::cout << line << "\n";
		accepted = std::stoi(line);

		file.close();
	}
	else {
		std::cout << "cannot read file";
	}

}

Order::~Order()
{
}

void Order::setRejected()
{
	rejected = true;
	customer->addRejectedOrder(*this);
}

void Order::cancel()
{
	cancelled = true;
	customer->addCancelledOrder(*this);
}

Order& Order::split(int amount)
{
	Order * newOrder = new Order(*this);
	newOrder->product.setAmount(product.getAmount() - amount);
	product.setAmount(amount);
	customer->addOrder(newOrder);
	return *newOrder;
}

void Order::makeDone()
{
	done = true;
	deliveryDate = Manager::TODAY;
	customer->addGoodOrder(*this);
}

void Order::save(std::string path)
{
	std::ofstream f;
	f.open(path);

	f << (product.getName() == ProductName::chips ? 0 : 1) << std::endl;
	f << product.getAmount() << std::endl;
	f << unitPrice << std::endl;
	f << recordDate << std::endl;
	f << deliveryDeathLine << std::endl;
	f << deliveryDate << std::endl;
	f << done << std::endl;
	f << cancelled << std::endl;
	f << rejected << std::endl;
	f << accepted;

	f.close();
}

std::string Order::about()
{
	char price[10];
	sprintf(price, "%4.2f", getTotalPrice());
	char date[30];
	sprintf(date, "%s", ctime(&deliveryDate));

	std::string aboutString;
	aboutString += customer->getFormattedName() + "  " + product.getStrName() + "  "
		+ std::to_string(product.getAmount()) + " kg  " + price + " EUR " + date;

	return aboutString;
}

bool operator==(const Order& lhs, const Order& rhs)
{
	return lhs.cancelled == rhs.cancelled
		&& lhs.deliveryDate == rhs.deliveryDate
		&& lhs.deliveryDeathLine == rhs.deliveryDeathLine
		&& lhs.done == rhs.done
		&& lhs.unitPrice == rhs.unitPrice
		&& lhs.product == rhs.product
		&& lhs.recordDate == rhs.recordDate
		&& lhs.rejected == rhs.rejected;
}