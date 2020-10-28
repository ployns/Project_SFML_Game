#include "meteor.h"

meteor::meteor(float speed, float x, float y,sf::Texture *texture)
{
	this->shape.setScale(sf::Vector2f(100,100));
	this->shape.setPosition(x, y);
	this->speed = speed;
	this->shape.setTexture(texture);
	this->shape.setTextureRect(sf::IntRect(0,0,texture->getSize().x,texture->getSize().y));
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
