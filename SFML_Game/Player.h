#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include<iostream>
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	~Player();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void actionAttack();
private:
	int state = 0;
	void update();
	void controller();
	Animation Animation;
	sf::RectangleShape body;
	//for animation
	float deltaTime = 0.0f;
	sf::Clock clock;
};

