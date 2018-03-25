#include "BusinessPartner.h"




BusinessPartner::BusinessPartner(std::string name)
	: name(name)
{
	formattedName = name;
	for (size_t i = 0; i < 15 - name.length(); i++)
		formattedName += ' ';
}

BusinessPartner::~BusinessPartner()
{
}
