#include "rigidBody.h"
using namespace std;

RigidBody::RigidBody(sf::Vector2f position) : position(position) {}

float RigidBody::prod(sf::Vector2f position2) 
{
	return position.x * position2.x + position.y * position2.y;
}
void RigidBody::update(float time) 
{
	if(force.x > 0 || force.y > 0)
		acceleration = force / mass;

	velocity += acceleration * time;
	position += velocity * time;
}

float RigidBody::getRadius() {
	return radius;
}

void RigidBody::setPosition(sf::Vector2f position) {
	this->position = position;
}

void RigidBody::setRadius(float radius) {
	this->radius = radius;
}

void RigidBody::AABB() 
{

}

sf::Vector2f RigidBody::getPosition()
{
	return position;
}

void RigidBody::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

sf::Vector2f RigidBody::getVelocity(){
	return velocity;
}

void RigidBody::setRestitution(float restitution) {
	this->restitution = restitution;
}
float RigidBody::getRestitution() {
	return restitution;
}

void RigidBody::setAcceleration(sf::Vector2f acceleration) {
	this->acceleration = acceleration;
}
sf::Vector2f RigidBody::getAcceleration() {
	return acceleration;
}

void RigidBody::setMass(float mass) {
	this->mass = mass;
	if(mass)
		invMass = 1 / mass;
}
float RigidBody::getMass() {
	return mass;
}

void RigidBody::setInvMass(float invMass) {
	this->invMass = invMass;
	mass = 1 / invMass;
}
float RigidBody::getInvMass() {
	return invMass;
}

void RigidBody::setLinearImpulse(float impulse) {
	this->linearImpulse = impulse;
}
float RigidBody::getLinearImpulse() {
	return linearImpulse;
}

void RigidBody::setCornerImpulse(float impulse) {
	this->cornerImpulse = impulse;
}
float RigidBody::getCornerImpulse() {
	return cornerImpulse;
}

void RigidBody::setForce(sf::Vector2f force) {
	this->force = force;
}
sf::Vector2f RigidBody::getForce() {
	return force;
}
