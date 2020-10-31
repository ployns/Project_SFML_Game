#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include<iostream>
class Fire
{
public:
	Fire(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	~Fire();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setActive(bool status);
	bool isActive();

	void setPosition(sf::Vector2f posi);
	sf::Vector2f getPosition();

private:
	void move(float deltaTime);
	bool active = false;
	Animation Animation;
	sf::Sprite body;
	sf::RectangleShape shape;

};
