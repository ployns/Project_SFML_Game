#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include "Animation.h"

class Item // => start: 4/11/2020 21.00PM.
{
public:
	Item(sf::Texture* texture, sf::Vector2f position);
	~Item();
	void Draw(sf::RenderWindow& window);
	bool checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	//sf::Vector2f positionPlayer();

private:
	double A = 2000;
	void move(float deltaTime);
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Vector2f getHalfSize();
	sf::Sprite body;
	sf::RectangleShape shape;
};

