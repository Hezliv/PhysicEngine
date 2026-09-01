#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
using namespace std;
class Shape {

};
class RigidBody {
	Shape* shape;
	struct AABB {
		sf::Vector2f center;
		sf::Vector2f halfSize;
	};
	AABB box;

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
public:
	RigidBody(sf::Vector2f position);

	void update(float time);
	AABB getAABB() const;

	float distance(RigidBody* another);
	bool collisionDetect(RigidBody* another);
	void resolveCollision(RigidBody* another);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;

	void setAcceleration(sf::Vector2f acceleration);
	sf::Vector2f getAcceleration() const;

	void setGravity(sf::Vector2f gravity);
	sf::Vector2f getGravity() const;

	void setForce(sf::Vector2f force);
	sf::Vector2f getForce() const;

	void setMass(float mass);
	float getMass() const;

	void setInvMass(float invMass);
	float getInvMass() const;

	void setRestitution(float restitution);
	float getRestitution() const;

	void setRadius(float radius = 20.0f);
	float getRadius() const;

	void setResistance(float resistance);
	float getResistance() const;

	void setFriction(float friction);
	float getFriction() const;
};