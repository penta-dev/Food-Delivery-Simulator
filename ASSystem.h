#pragma once

#include "common.h"
#include "ASOrder.h"
#include "ASCourier.h"

class ASSystem
{
public:
	virtual void addOrder(ASOrder order);
	virtual void addCourier(ASCourier courier);

	virtual void process(float time);
public:
	vector<ASOrder> _cooking_orders;

	vector<ASOrder> _waiting_foods;
	vector<ASCourier> _waiting_couriers;

	vector<ASOrder> _deliveried_foods;
	vector<ASCourier> _deliveried_couriers;
};

