#include "geometry.h"
#include "System.h"
#include "random.h"
#include <iostream>
#include <math.h>

void System::step() {
	// wet friction
	for (auto& body : bodies) {
		body.vel -= body.vel * frictionK * dt / body.m;
		body.w -= body.w * frictionK * dt / body.m;
	}

	// gravity
	for (auto& body : bodies)
		body.vel += g * dt;

	// border collision
	double forceValue = 100;
	double power = 1;
	for (auto& body : bodies) {
		for (auto& point : body.points) {
			auto p = point + body.pos;
			if (p.x < 0)
				force(body, p, { forceValue * (-pow(p.x, power)), 0 });
			if (p.y < 0)
				force(body, p, { 0, forceValue * (-pow(p.y, power)) });
			if (p.x > border.x)
				force(body, p, { -forceValue * (pow(p.x - border.x, power)), 0 });
			if (p.y > border.y)
				force(body, p, { 0, -forceValue * (pow(p.y - border.y, power)) });
		}
	}

	// body collision
	forceValue = 10;
	for (auto& body1 : bodies) {
		for (auto& point : body1.points) {
			auto p1 = point + body1.pos;
			for (auto& body2 : bodies) {
				if (&body1 == &body2)
					continue;

				// shifted points
				auto points = body2.points;
				for (auto& p : points)
					p += body2.pos;

				if (geom::inPolygon(p1, points)) {
					// finding nearest part
					std::pair<Vec2, Vec2> part;
					double minDist = 1e7;
					for (int i = 0; i < points.size(); i++) {
						int j = (i + 1) % points.size();
						double dist = geom::distance(p1, points[i], points[j]);
						if (dist < minDist) {
							minDist = dist;
							part = { points[i], points[j]};
						}
					}
					
					// relative vel
					Vec2 rl = geom::rotate(p1 - body1.vel, M_PI / 2) * body2.w;
					double k = 100;// *pow(minDist, 1);

					// applying force
					Vec2 dir = geom::rotate(part.first - part.second, M_PI / 2) / geom::distance(part.first, part.second);
					//std::cout << dir.x << " " << dir.y << "\n";
					force(body1, p1, dir * (forceValue * k));
					force(body2, p1, dir * ( -forceValue * k));
				}
			}
		}
	}

	// moving bodies
	for (auto& body : bodies) {
		body.pos += body.vel * dt;
		for (auto& point : body.points)
			point = geom::rotate(point, body.w * dt);
	}
}