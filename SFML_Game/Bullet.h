#pragma once
#include "Fire.h"
#include<SFML\Graphics.hpp>
#include<iostream>
class Bullet
{
public:
	Bullet(sf::Texture* texture);
	~Bullet();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f positionPlayer;
	sf::Event* evnt;
	bool canAttack();
private:
	void action();
	std::vector<Fire> fires;
	int fire_num = 5;
	float deltaTime = 0.0f;
	sf::Clock clock;
	// debug fire press
	bool isSpacebarPrees = false;
};

