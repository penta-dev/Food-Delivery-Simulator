#include "pch.h"
#include "ASCourier.h"


ASCourier::ASCourier()
{
	_delivery_time = 0;
}
string ASCourier::to_string()
{
	char str[512];
	sprintf_s(str, "%s, %.2f, %.2f, %.2f", _specific_order._name.c_str(), _created_time, _arr_time, _delivery_time);
	return str;
}