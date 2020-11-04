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
	deltaTime = clock.restart().asSeconds();
	if (this->body.getPosition().x > -500) {
		window.draw(body);
		this->move(deltaTime);
	}
}

void Item::move(float deltaTime)
{
	//std::cout << "Move" << std::endl;
	this->body.move(sf::Vector2f(deltaTime * -300, sin(this->A-=0.005)));
}

bool Item::checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer)
{
	//cout << "Player : "<< posPlayer.x << " " << posPlayer.y << endl;
	//cout << "Item : " << this->body.getPosition().x << " " << this->body.getPosition().y << endl;
	return (abs(posPlayer.x - this->body.getPosition().x) < (halfSizePlayer.x * 0.8 + this->getHalfSize().x * 0.6) &&
		abs(posPlayer.y - this->body.getPosition().y) < (halfSizePlayer.y * 0.8 + this->getHalfSize().y * 0.6));
}

void Item::setPosition(sf::Vector2f pos)
{
	this->body.setPosition(pos);
}

sf::Vector2f Item::getPosition()
{
	return sf::Vector2f(this->body.getPosition());
}

sf::Vector2f Item::getHalfSize()
{
	sf::Vector2u size = this->body.getTexture()->getSize();
	return sf::Vector2f(size.x/2, size.y/2);
}
