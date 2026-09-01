#pragma once
#include "rigidBody.h"
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;

class Particle 
{
	sf::CircleShape* circle; // connect memory pool
	float radius = 4.0f;
public:
	Particle(float radius, sf::Vector2f position, sf::Color color = sf::Color::White);
	inline static bool glow = false;
	sf::CircleShape* getCircle();
};