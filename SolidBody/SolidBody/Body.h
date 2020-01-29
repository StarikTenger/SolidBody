#pragma once
#include "geometry.h"
#include "Color.h"
#include <vector>

class Body {
public:
	double m = 1;
	double i = 10;
	double dir = 0;
	double w = 0;

	Vec2 pos;
	Vec2 vel;

	std::vector<Vec2> points;

	Color col;

	Body() {};
};

