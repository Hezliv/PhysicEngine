#include "particle.h"

Particle::Particle(float radius, sf::Vector2f position, sf::Color color) {
	circle = new sf::CircleShape(); // rewrite with memory pool
	circle->setFillColor(color);
	circle->setOrigin({ radius, radius });
	circle->setRadius(radius);
	circle->setPosition(position);
}

sf::CircleShape* Particle::getCircle() {
	return circle;
}

