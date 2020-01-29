#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace geom;
using namespace random;
using namespace std;

System::System() {
	rectBody(100, { 200, 200 }, { 197, 50 }, 0.2, { 120, 120, 0 });
	rectBody(100, { 320, 475 }, { 200, 51 }, 0, { 120, 120, 0 });
	rectBody(100, { 200, 350 }, { 198, 47 }, M_PI / 2 + 0.1, { 120, 120, 0 });
	rectBody(100, { 500, 200 }, { 203, 102 }, M_PI / 2 + 0.1, { 120, 120, 0 });
	//bodies.back().vel = { -5, 0 };
	//bodies.back().w = 0.1;
}

System::~System() {
}

void System::rectBody(double m, Vec2 pos, Vec2 box, double dir, Color col) {
	Body body;
	body.col = col;
	body.pos = pos;
	body.m = m;
	body.i = m*box.x * box.y/2;

	body.points = {
		{ -box.x / 2, -box.y / 2 },
		{ box.x / 2, -box.y / 2 },
		{ box.x / 2, box.y / 2 },
		{ -box.x / 2, box.y / 2 }
	};

	for (auto& point : body.points)
		point = geom::rotate(point, dir);

	bodies.push_back(body);
}

void System::force(Body& body, Vec2 pos, Vec2 f) {
	// linear
	body.vel += f / body.m * dt;

	// angular
	auto l = pos - body.pos;
	body.w += geom::crossProd(l, f) / body.i * dt;
}
