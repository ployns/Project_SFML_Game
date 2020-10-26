#include "meteor.h"

meteor::meteor(float speed, float x, float y,sf::Color color)
{
	this->shape.setSize(sf::Vector2f(100,100));
	this->shape.setPosition(x, y);
	this->shape.setFillColor(color);
	this->speed = speed;
}

meteor::~meteor()
{
	std::cout << "Delete";
}

void meteor::update(float x,float y)
{
	this->shape.move(x*this->speed, y*this->speed);
}

sf::RectangleShape meteor::getShape()
{
	return this->shape;
}
