#pragma once

#include "common.h"

class ASOrder
{
public:
	string _id;
	string _name;
	float _prep_time;
	float _created_time;
	float _delivery_time;

public:
	static vector<ASOrder> g_samples;
	static void CreateSamples();
	static ASOrder CreateRandomOrder();

	ASOrder();
	string to_string();
};