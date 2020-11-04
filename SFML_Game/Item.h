#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include "Animation.h"

class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2f position);
	~Item();
	void Draw(sf::RenderWindow& window);
	void move(float deltaTime);
	//sf::Vector2f positionPlayer();

private:
	sf::Sprite body;
	sf::RectangleShape shape;
};

