#pragma once
#include <vector>
#include <fstream>
#include "geometry.h"
#include "Body.h"
#include <string>
#include <SFML/Graphics.hpp>


class System{
public:
	double dt = 0.02;
	double frictionK = 1;
	double chunkSize = 20;
	double collisionK = 0.5;

	Vec2 border = { 600, 600 };
	Vec2 g = { 0, 0.1};

	std::vector<Body> bodies;

	System();
	~System();

	void rectBody(double m, Vec2 pos, Vec2 box, double dir, Color col);
	void force(Body& body, Vec2 pos, Vec2 f);
	void step();
	
};