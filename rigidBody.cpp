#include "rigidBody.h"
using namespace std;

RigidBody::RigidBody(sf::Vector2f position) : position(position) {
	box.halfSize = { radius, radius };
	box.center = { radius, radius };
}

float RigidBody::dot(sf::Vector2f position2) {
	return position.x * position2.x + position.y * position2.y;
}

float RigidBody::distance(RigidBody* another) {
	float dx = position.x - another->position.x;
	float dy = position.y - another->position.y;
	return sqrt(dx * dx + dy * dy); // redo without sqrt

}

bool RigidBody::collisionDetect(RigidBody* another) {
	return distance(another) < radius + another->radius;
}

void RigidBody::resolveCollision(RigidBody* another) {

}

void RigidBody::update(float time) {	
	acceleration = gravity + (force / mass);
	acceleration -= velocity * airResistance;
	velocity += acceleration * time;
	position += velocity * time;
}

float RigidBody::getRadius() const {
	return radius;
}

void RigidBody::setPosition(sf::Vector2f position) {
	this->position = position;
}

void RigidBody::setGravity(sf::Vector2f gravity) {
	this->gravity = gravity;
}
sf::Vector2f RigidBody::getGravity() const {
	return gravity;
}

void RigidBody::setRadius(float radius) {
	this->radius = radius;
	box.halfSize = { radius, radius };
	box.center = { radius, radius };
}

RigidBody::AABB RigidBody::getAABB()  const {
	return box;
}

sf::Vector2f RigidBody::getPosition() const {
	return position;
}

void RigidBody::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

sf::Vector2f RigidBody::getVelocity() const {
	return velocity;
}

void RigidBody::setRestitution(float restitution) {
	this->restitution = restitution;
}
float RigidBody::getRestitution() const {
	return restitution;
}

void RigidBody::setAcceleration(sf::Vector2f acceleration) {
	this->acceleration = acceleration;
}
sf::Vector2f RigidBody::getAcceleration() const {
	return acceleration;
}

void RigidBody::setMass(float mass) {
	this->mass = mass;
	if(mass)
		invMass = 1 / mass;
}
float RigidBody::getMass() const {
	return mass;
}

void RigidBody::setInvMass(float invMass) {
	this->invMass = invMass;
	mass = 1 / invMass;
}
float RigidBody::getInvMass() const {
	return invMass;
}

void RigidBody::setForce(sf::Vector2f force) {
	this->force = force;
}
sf::Vector2f RigidBody::getForce() const {
	return force;
}

void RigidBody::setResistance(float resistance) {
	this->airResistance = resistance;
}
float RigidBody::getResistance() const {
	return airResistance;
}

void RigidBody::setFriction(float friction) {
	this->friction = friction;
}
float RigidBody::getFriction() const {
	return friction;
}

