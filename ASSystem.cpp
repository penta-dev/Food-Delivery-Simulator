#include "ASSystem.h"

void ASSystem::addOrder(ASOrder order)
{
	_cooking_orders.push_back(order);
}
void ASSystem::addCourier(ASCourier courier)
{
	_waiting_couriers.push_back(courier);
}
void ASSystem::process(float time)
{
	// cooking -> waiting
	for (int i = 0; i < _cooking_orders.size(); i++)
	{
		ASOrder& order = _cooking_orders[i];
		if (order._created_time + order._prep_time < time)
		{// cooked
			_waiting_foods.push_back(order);
			_cooking_orders.erase(_cooking_orders.begin() + i);
			break;
		}
	}
}
