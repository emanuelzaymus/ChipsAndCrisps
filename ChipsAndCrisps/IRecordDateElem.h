#pragma once

#include <ctime>

#include "structures\heap_monitor.h"


class IRecordDateElem
{
public:
	IRecordDateElem();
	~IRecordDateElem();

	virtual time_t getRecordDate() = 0;

	friend bool operator==(const IRecordDateElem& lhs, const IRecordDateElem& rhs);
};

