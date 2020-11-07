#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
#include "Animation.h"
class Meteor
{
public:
	Meteor(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	~Meteor();
	void Draw(sf::RenderWindow& window);
	bool checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void Update(float deltaTime);
	std::vector<Meteor> meteorlist;

private:
	void move(float deltaTime);
	float deltaTime = 0.0f;
	sf::Clock clock;
	Animation Animation;
	sf::Vector2f getHalfSize();
	sf::RectangleShape shape;
	sf::Sprite body;

};

