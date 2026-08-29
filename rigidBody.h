#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
class Shape {

};
class RigidBody {
	Shape* shape;
	sf::Vector2f position = { 0.0f, 0.0f };
	sf::Vector2f velocity = { 0.0f, 0.0f };
	sf::Vector2f acceleration = { 0.0f, 0.0f };
	sf::Vector2f force = { 0.0f, 0.0f };
	sf::Vector2f gravity = { 0.0f, 0.0f };
	float restitution = 0.8f;
	float mass = 1.0f;
	float invMass = mass == 0 ? 0 : 1 / mass;
	float radius;
	float friction = 0.4f;
	float airResistance = 0.1f;
	float dot(sf::Vector2f coords2);

	struct AABB {
		sf::Vector2f center;
		sf::Vector2f halfSize;
	};
	AABB box;
public:
	RigidBody(sf::Vector2f position);

	void update(float time);
	AABB getAABB();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity();

	void setAcceleration(sf::Vector2f acceleration);
	sf::Vector2f getAcceleration();

	void setGravity(sf::Vector2f gravity);
	sf::Vector2f getGravity();

	void setForce(sf::Vector2f force);
	sf::Vector2f getForce();

	void setMass(float mass);
	float getMass();

	void setInvMass(float invMass);
	float getInvMass();

	void setRestitution(float restitution);
	float getRestitution();

	void setRadius(float radius = 20.0f);
	float getRadius();

	void setResistance(float resistance);
	float getResistance();

	void setFriction(float friction);
	float getFriction();
};