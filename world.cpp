#include<iostream>
#include "rigidBody.h"
#include "particle.h"

using namespace std;
class Engine {
	float gravity = 900.3f;
	unsigned int height = 600;
	unsigned int width = 800;

	void pushMove(RigidBody& body, sf::Vector2f force) {
		addForce(body, force);
	}

	void pullMove(RigidBody& body, sf::Vector2f force) {
		addForce(body, force);
	}
public:
	void borderCollision(RigidBody& body)
	{
		sf::Vector2f pos = body.getPosition();
		sf::Vector2f vel = body.getVelocity();
		float rad = body.getRadius();
		float rest = body.getRestitution();

		if (pos.x < 0)
		{
			vel.x = -vel.x * rest;
			body.setPosition({ 0, pos.y });
		}
		if (pos.x + rad > width)
		{
			vel.x = -vel.x * rest;
			body.setPosition({ width - rad, pos.y });
		}
		if (pos.y < 0)
		{
			body.setPosition({ pos.x, 0 });
			vel.y = -vel.y * rest;
		}
		if (pos.y + rad > height)
		{
			body.setPosition({ pos.x, height - rad });
			vel.y = -vel.y * rest;
		}
		body.setVelocity(vel);
	}

	void process() {
		sf::RenderWindow window(sf::VideoMode(sf::Vector2u({ width, height })), "");
		RigidBody body(sf::Vector2f({ (float)width / 2, (float)height / 2 }));
		body.setAcceleration({ 0, gravity });
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
				if (event->is<sf::Event::MouseButtonPressed>())
				{
					sf::Vector2i mouse = sf::Mouse::getPosition(window);
					sf::Vector2f f;
					sf::Vector2f pos = body.getPosition();
					if (event->is<sf::Event::MouseButtonPressed>())
					{
						f = { pos.x - mouse.x, pos.y - mouse.y };
						pushMove(body, f);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						f = { mouse.x - pos.x, mouse.y - pos.y };
						pullMove(body, f);
					}
				}
			}
			addForce(body, { 100.0f, 0.0f });
			body.update(dt.asSeconds());
			borderCollision(body);
			p.getCircle()->setPosition(body.getPosition());
			window.draw(*p.getCircle());
			window.display();
		}
	}

	void addForce(RigidBody& body, sf::Vector2f force) {
		body.setForce(force);
	}
};

int main() {
	Engine e;
	e.process();
}