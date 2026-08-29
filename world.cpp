#include<iostream>
#include "rigidBody.h"
#include "particle.h"
#include<math.h>
using namespace std;
#include "SpatialGrid.cpp"
class Engine {
	float gravity = 900.3f;
	unsigned int height;
	unsigned width;
	SpatialGrid* grid;

	void mouseInteraction(RigidBody& body, sf::Vector2f force) {
		addForce(body, force);
	}
public:
	Engine(int width, int height, float cellSize = 64.0f) {
		int cell = static_cast<int>(cellSize);
		

		this->width = (width / cell) * cell;
		this->height = (height / cell) * cell;
		grid = new SpatialGrid(width, height, cellSize);
	}

	~Engine() {
		delete grid;
	}

	void borderCollision(RigidBody& body, double dt) {
		sf::Vector2f pos = body.getPosition();
		sf::Vector2f vel = body.getVelocity();
		float rad = body.getRadius();
		float rest = body.getRestitution();

		if (pos.x - rad < 0)
		{
			vel.x = -vel.x * rest;
			vel.y *= (1.0f - body.getFriction() * dt);
			body.setPosition({ rad, pos.y });
		}
		if (pos.x + rad > width)
		{
			vel.x = -vel.x * rest; 
			vel.y *= (1.0f - body.getFriction() * dt);
			body.setPosition({ width - rad, pos.y });
		}
		if (pos.y - rad < 0)
		{
			body.setPosition({ pos.x, rad });
			vel.y = -vel.y * rest;
			vel.x *= (1.0f - body.getFriction() * dt);
		}
		if (pos.y + rad > height)
		{
			body.setPosition({ pos.x, height - rad });
			vel.y = -vel.y * rest;
			vel.x *= (1.0f - body.getFriction() * dt);
		}
		body.setVelocity(vel);
	}

	void process() {
		sf::RenderWindow window(sf::VideoMode(sf::Vector2u({ width, height })), "");
		vector<RigidBody*> bodies(10);
		for (int i = 0; i < bodies.size(); i++)	{
			bodies[i] = new RigidBody({ (float)width / 2, i * grid->getCellSize() });
			bodies[i]->setGravity({ 0, gravity });
			bodies[i]->setRadius(10.0f + i);
		}
		//RigidBody body(sf::Vector2f({ (float)width / 2, (float)height / 2 }));
		//body.setGravity({ 0, gravity });
		//body.setRadius(20.0f);
		vector<Particle*> particles(bodies.size());
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i] = new Particle(bodies[i]->getRadius(), bodies[i]->getPosition());
		}
		//Particle p(body.getRadius(), body.getPosition());
		sf::Clock clock;
		clock.start();
		while (window.isOpen()) {
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
			
			for (int i = 0; i < bodies.size(); i++)
			{
				//addForce(body, { 100.0f, 0.0f });
				bodies[i]->update(dt.asSeconds());
				borderCollision(*bodies[i], dt.asSeconds());
				particles[i]->getCircle()->setPosition(bodies[i]->getPosition());

			}
			grid->refresh(bodies);

			auto pairs = grid->getUniquePairs();

			for (auto& [a, b] : pairs) {
				if (collisionDetect(a, b)) {
					resolveCollision(a, b);
				}
			}

			grid->draw(window);
			for (auto& p : particles)
				window.draw(*p->getCircle());
			window.display();
		}
	}

	bool collisionDetect(RigidBody* a, RigidBody* b) {
		return a->collisionDetect(b);
	}

	void resolveCollision(RigidBody* a, RigidBody* b) {
		
	}

	void addForce(RigidBody& body, sf::Vector2f& force) {
		body.setForce(force);
	}

	void addImpulse(RigidBody& body, sf::Vector2f& force) {
		body.setForce(force);
	}
};

int main() {
	Engine e(1000, 800);
	e.process();
}