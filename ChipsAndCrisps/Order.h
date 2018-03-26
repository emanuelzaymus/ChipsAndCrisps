#pragma once

#include <ctime>
#include <ostream>

#include "structures\heap_monitor.h"

#include "Product.h"
#include "IRecordDateElem.h"

#include "Customer.h"
//class Customer;

class Order : IRecordDateElem
{
private:
	Customer &customer;
	Product product;
	double price;
	time_t recordDate;
	time_t deliveryDeathLine;
	time_t deliveryDate;
	bool done = false;
	bool cancelled = false;
	bool rejected = false;
	bool accepted = true;

public:
	Order(Customer &customer, Product product, double price, time_t deliveryDeathLine);
	~Order();

	void setRecordDate(time_t date) { recordDate = date; }
	time_t getRecordDate() { return recordDate; }
	time_t getDeliveryDeathLine() { return deliveryDeathLine; }
	void setRejected();
	void setAccepted(bool b) { accepted = b; }
	double getTotalPrice() const { return price * product.getAmount(); }
	Product getProduct() { return product; }

	friend std::ostream& operator<<(std::ostream &strm, const Order &obj);
	friend bool operator==(const Order& lhs, const Order& rhs);
};

inline std::ostream& operator<<(std::ostream &strm, const Order &obj) {
	char amount[10];
	sprintf(amount, "%4d", obj.product.getAmount());
	char chPrice[10];
	sprintf(chPrice, "%1.2f", obj.price);
	char chTotal[10];
	sprintf(chTotal, "%8.2f", obj.getTotalPrice());
	char date[30];
	//sprintf(date, "%s", ctime(&obj.recordDate));		// change
	sprintf(date, "%s", ctime(&obj.deliveryDeathLine));// todo change

	return strm << obj.customer << "  " << obj.product.getStrName() << "  "
		<< amount << "  " << chPrice << "  " << chTotal << "  "
		<< (obj.cancelled ? "Cancelled" : "Waiting  ") << "  " << date;
}
