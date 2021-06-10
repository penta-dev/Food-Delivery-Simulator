#include "pch.h"
#include "ASOrder.h"
#include "jute.h"

vector<ASOrder> ASOrder::g_samples;

ASOrder ASOrder::CreateRandomOrder()
{
    int n = g_samples.size();
    assert(n > 0, "please make samples at first");
    int index = rand() % n;
	return g_samples[index];
}

void ASOrder::CreateSamples()
{
    ifstream in("dispatch_orders.json");
    string str = "";
    string tmp;
    while (getline(in, tmp)) str += tmp;
    jute::jValue v = jute::parser::parse(str);
    for (int i = 0; i < v.size(); i++)
    {
        ASOrder order;
        order._id = v[i]["id"].as_string();
        order._name = v[i]["name"].as_string();
        order._prep_time = v[i]["prepTime"].as_int();
        g_samples.push_back(order);
    }
}
ASOrder::ASOrder()
{
    _delivery_time = 0;
}
string ASOrder::to_string()
{
    char str[512];
    sprintf_s(str, "%s, %.2f, %.0f, %.2f", _name.c_str(), _created_time, _prep_time, _delivery_time);
    return str;
}