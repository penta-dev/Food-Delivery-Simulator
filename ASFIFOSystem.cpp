#include "ASFIFOSystem.h"


void ASFIFOSystem::process(float time)
{
	ASSystem::process(time);

	for (int i = 0; i < _waiting_couriers.size(); i++)
	{
		ASCourier& c = _waiting_couriers[i];
		if (_waiting_foods.size())
		{
			int index = rand() % _waiting_foods.size();
			ASOrder& food = _waiting_foods[index];

			c._delivery_time = time;
			c._specific_order = food;	// changed
			food._delivery_time = time;

			_deliveried_couriers.push_back(c);
			_deliveried_foods.push_back(food);

			_waiting_foods.erase(_waiting_foods.begin() + index);
			_waiting_couriers.erase(_waiting_couriers.begin() + i);

			return;
		}
	}
}
