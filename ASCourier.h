#pragma once

#include "ASOrder.h"

class ASCourier
{
public:
	float _created_time;
	float _arr_time;
	float _delivery_time;
	ASOrder _specific_order;
public:
	ASCourier();
	string to_string();
};

