#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>
class meteor
{
public:
	meteor(float speed,float x,float y,sf::Color color);
	~meteor();

	void update(float x, float y);
	sf::RectangleShape getShape();

private:
	int hp;
	float speed;
	sf::RectangleShape shape;

};

