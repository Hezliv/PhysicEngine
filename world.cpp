#include<iostream>
#include "rigidBody.h"
#include<math.h>
using namespace std;
#include "SpatialGrid.cpp"
class Engine {
	float gravity = 900.3f;
	size_t maxBodies = 5000;
	unsigned int height;
	unsigned int width;
	SpatialGrid* grid;

	void mouseInteraction(RigidBody& body, sf::Vector2f force) {
		addForce(body, force);
	}
public:
	Engine(int width, int height, float cellSize = 64.0f) {
		int cell = static_cast<int>(cellSize);
		
		this->width = (width / cell) * cell;
		this->height = (height / cell) * cell;
		grid = new SpatialGrid(this->width, this->height, maxBodies, cellSize);
	}

	~Engine() {
		delete grid;
	}

	void borderCollision(RigidBody& body, double dt) {
		sf::Vector2f pos = body.getPosition();
		sf::Vector2f old = body.getOldPosition();
		sf::Vector2f vel = pos - old;

		float rad = body.getRadius();
		float rest = body.getRestitution();

		if (pos.x - rad < 0)
		{
			pos.x = rad;
			vel.x = -vel.x * rest;
			vel.y *= (1.0 - body.getFriction() * dt);
		}
		else if (pos.x + rad > width)
		{
			pos.x = width - rad;
			vel.x = -vel.x * rest; 
			vel.y *= (1.0f - body.getFriction() * dt);
		}
		if (pos.y - rad < 0)
		{
			pos.y = rad;
			vel.y = -vel.y * rest;
			vel.x *= (1.0f - body.getFriction() * dt);
		}
		else if (pos.y + rad > height)
		{
			pos.y = height - rad;
			vel.y = -vel.y * rest;
			vel.x *= (1.0f - body.getFriction() * dt);
		}	
		old.x = pos.x - vel.x;
		old.y = pos.y - vel.y;

		body.setPosition(pos);
		body.setOldPosition(old);
	}

	void process(int amountOfBodies) {
		if (maxBodies < amountOfBodies)
		{
			maxBodies = amountOfBodies;
			grid->resize(maxBodies);
		}
		sf::RenderWindow window(sf::VideoMode(sf::Vector2u({ width, height })), "");
		window.setPosition({ 0, 0 });
		vector<RigidBody*> bodies(amountOfBodies);
		int colsCount = 80;
		float spacing = 24.0f;
		for (size_t i = 0; i < bodies.size(); i++) {
			int col = i % colsCount;
			int row = i / colsCount;

			float x = 100.0f + col * spacing;
			float y = 50.0f + row * spacing;

			bodies[i] = new RigidBody({ x, y });
			bodies[i]->setGravity({ 0.0f, gravity });
			bodies[i]->setRadius(10.0f);
		}

		vector<sf::CircleShape*> particles(bodies.size());
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i] = new sf::CircleShape();
			particles[i]->setOrigin({ bodies[i]->getRadius(), bodies[i]->getRadius() });
			particles[i]->setFillColor(sf::Color::Red);
			particles[i]->setPosition(bodies[i]->getPosition());
			particles[i]->setRadius(bodies[i]->getRadius());
		}
		
		//auto vec = grid->drawGrid(window);
		sf::Clock clock;
		clock.start();
		while (window.isOpen()) {
			grid->clear();
			window.clear(sf::Color::Black);

			sf::Time dt = clock.restart();
			while (optional<sf::Event> event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>())
					window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f m = window.mapPixelToCoords(pixelPos);
				for(RigidBody* body : bodies)
				{
					sf::Vector2f pos = body->getPosition();
					sf::Vector2f dist = { 0, 0 };
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
						dist = { pos.x - m.x, pos.y - m.y };
					}
					else {
						dist = { m.x - pos.x, m.y - pos.y };
					}
					float len = sqrt(dist.x * dist.x + dist.y * dist.y);
					if (len > 0.000001f)
						dist /= len;
					sf::Vector2f f = dist * 5000.0f;
					mouseInteraction(*body, f);
				}
			}
			else {
				for(auto& body : bodies)
					body->setForce({ 0,0 });
			}

			float dtSec = dt.asSeconds();
			if (dtSec > 0.02f) dtSec = 0.02f;

			for (auto& body : bodies) {
				body->update(dtSec);
			}
			grid->refresh(bodies);
			for(int i = 0; i < 8; i++)
			{
				grid->resolveCollision(bodies);
				for (auto& body : bodies) {
					borderCollision(*body, dtSec);
				}
			}
			
			for (int i = 0; i < bodies.size(); i++)
			{
				particles[i]->setPosition(bodies[i]->getPosition());
			}
			grid->mapBodiesToCell(window, sf::Color::White);
			grid->drawGrid(window);

			//window.draw(vec);
			for (auto& p : particles)
				window.draw(*p);
			window.display();
		}
	}

	bool collisionDetect(RigidBody* a, RigidBody* b) {
		return a->collisionDetect(b);
	}

	void addForce(RigidBody& body, sf::Vector2f& force) {
		body.setForce(force);
	}

	void addImpulse(RigidBody& body, sf::Vector2f& force) {
		body.setForce(force);
	}
};

int main() {
	Engine e(1820, 980, 64);
	e.process(4000);
}

