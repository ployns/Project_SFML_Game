#include "Item.h"

Item::Item(sf::Texture* texture, sf::Vector2f position)
{
	this->body.setScale(sf::Vector2f(1, 1));
	this->body.setPosition(position);
	this->body.setTexture(*texture);
}

Item::~Item()
{
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Item::move(float deltaTime)
{
		//std::cout << "Move" << std::endl;
		this->body.move(sf::Vector2f(deltaTime * -200, 0));
}
