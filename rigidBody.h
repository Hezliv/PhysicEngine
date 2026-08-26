#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
class RigidBody {
	sf::Vector2f position = { 0.0f, 0.0f };
	float restitution = 0.8f;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	sf::Vector2f acceleration = { 0.0f, 0.0f };
	float mass = 1.0f;
	float invMass = mass == 0 ? 0 : 1 / mass;
	float radius;
	float linearImpulse = 0.0f;
	float cornerImpulse = 0.0f;
	sf::Vector2f force = { 0.0f, 0.0f };
	float prod(sf::Vector2f coords2);

public:
	RigidBody(sf::Vector2f position);
	void update(float time);
	void AABB();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	void setRadius(float radius = 20.0f);
	float getRadius();

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity();

	void setRestitution(float restitution);
	float getRestitution();

	void setAcceleration(sf::Vector2f acceleration);
	sf::Vector2f getAcceleration();

	void setMass(float mass);
	float getMass();

	void setInvMass(float invMass);
	float getInvMass();

	void setLinearImpulse(float impulse);
	float getLinearImpulse();

	void setCornerImpulse(float impulse);
	float getCornerImpulse();

	void setForce(sf::Vector2f force);
	sf::Vector2f getForce();


};