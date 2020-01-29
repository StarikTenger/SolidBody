#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "GGKP");
	loadTextures();
	
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));

	for (auto& body : sys.bodies)
		for (int i = 0; i < body.points.size(); i++) {
			int j = (i + 1) % body.points.size();
			auto p1 = body.points[i] + body.pos;
			auto p2 = body.points[j] + body.pos;
			line(p1.x, p1.y, p2.x, p2.y, { 255, 255, 255 });
		}
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
