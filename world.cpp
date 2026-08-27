#include<iostream>
#include "rigidBody.h"
#include "particle.h"
#include<math.h>

using namespace std;
class Engine {
	float gravity = 900.3f;
	unsigned int height = 600;
	unsigned int width = 800;

	void mouseInteraction(RigidBody& body, sf::Vector2f force) {
		addForce(body, force);
	}
public:
	void borderCollision(RigidBody& body, double dt)
	{
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
		RigidBody body(sf::Vector2f({ (float)width / 2, (float)height / 2 }));
		body.setGravity({ 0, gravity });
		body.setRadius(20.0f);
		Particle p(body.getRadius(), body.getPosition());
		sf::Clock clock;
		clock.start();
		while (window.isOpen())
		{
			window.clear(sf::Color::Black);
			sf::Time dt = clock.restart();
			while (optional<sf::Event> event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f m = window.mapPixelToCoords(pixelPos);
				sf::Vector2f pos = body.getPosition();
				sf::Vector2f dist = { 0, 0 };
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					dist = { pos.x - m.x, pos.y - m.y };
				}
				else
				{
					dist = { m.x - pos.x, m.y - pos.y };
				}
				float len = sqrt(dist.x * dist.x + dist.y * dist.y);
				if (len > 0.000001f)
					dist /= len;
				sf::Vector2f f = dist * 5000.0f;
				mouseInteraction(body, f);
			}
			else
			{
				body.setForce({ 0,0 });
			}
			
			//addForce(body, { 100.0f, 0.0f });
			body.update(dt.asSeconds());
			borderCollision(body, dt.asSeconds());
			p.getCircle()->setPosition(body.getPosition());
			window.draw(*p.getCircle());
			window.display();
		}
	}

	bool checkCollision() {

	}

	void addForce(RigidBody& body, sf::Vector2f force) {
		body.setForce(force);
	}

	void addImpulse(RigidBody& body, sf::Vector2f force) {
		body.setForce(force);
	}
};

int main() {
	Engine e;
	e.process();
}