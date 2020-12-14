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

void Item::Draw(sf::RenderWindow& window, float _deltatime)
{
	deltaTime = clock.restart().asSeconds();
	if (this->body.getPosition().x > -500) {
		window.draw(body);
		this->move(_deltatime);
	}
}

void Item::move(float deltatime)
{
	//std::cout << "Move" << std::endl;
	this->body.move(sf::Vector2f(deltatime * -300, sin(this->A-=0.005)));
}

bool Item::checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer)
{
	//cout << "Player : "<< posPlayer.x << " " << posPlayer.y << endl;
	//cout << "Item : " << this->body.getPosition().x << " " << this->body.getPosition().y << endl;
	return (abs(posPlayer.x - this->body.getPosition().x) < (halfSizePlayer.x * 0.6 + this->getHalfSize().x * 0.6) &&
		abs(posPlayer.y - this->body.getPosition().y) < (halfSizePlayer.y * 0.6 + this->getHalfSize().y * 0.6));
}

void Item::setPosition(sf::Vector2f pos)
{
	this->body.setPosition(pos);
}

sf::Vector2f Item::getPosition()
{
	return sf::Vector2f(this->body.getPosition());
}

void Item::reset(float pos)
{
	if (this->body.getPosition().x <= pos) {
		this->body.setPosition(sf::Vector2f(rand() % 8000 + 4000, rand() % 550 + 100));
	}
}

sf::Vector2f Item::getHalfSize()
{
	sf::Vector2u size = this->body.getTexture()->getSize();
	return sf::Vector2f(size.x/2, size.y/2);
}
