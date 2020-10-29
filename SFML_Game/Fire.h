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

private:
	Animation Animation;
	sf::Sprite fire;
};

