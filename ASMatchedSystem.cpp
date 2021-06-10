#include "ASMatchedSystem.h"

void ASMatchedSystem::process(float time)
{
	ASSystem::process(time);

	for (int i = 0; i < _waiting_couriers.size(); i++)
	{
		ASCourier& c = _waiting_couriers[i];
		string str = c._specific_order._id;
		for (int j = 0; j < _waiting_foods.size(); j++)
		{
			ASOrder& food = _waiting_foods[j];
			if (str == food._id)	// pick only specified foods
			{
				c._delivery_time = time;
				food._delivery_time = time;

				_deliveried_couriers.push_back(c);
				_deliveried_foods.push_back(food);

				_waiting_foods.erase(_waiting_foods.begin() + j);
				_waiting_couriers.erase(_waiting_couriers.begin() + i);

				return;
			}
		}
	}
}
