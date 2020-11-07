#include "Meteor.h"

Meteor::Meteor(sf::Texture* texture, sf::Vector2u imageCount, float switchTime ,sf::Vector2f position) :
	Animation(texture, imageCount, switchTime)
{
	this->body.setScale(sf::Vector2f(1.5, 1.5));
	this->body.setPosition(position);
	this->body.setTexture(*texture);
	//this->Update(deltaTime);
}

Meteor::~Meteor()
{
}

void Meteor::Draw(sf::RenderWindow& window)
{
	deltaTime = clock.restart().asSeconds();
	if (this->body.getPosition().x > -500) {
		
		window.draw(body);
		this->Update(deltaTime);
		this->move(deltaTime);
	}
}

bool Meteor::checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer)
{
	return (abs(posPlayer.x - this->body.getPosition().x) < (halfSizePlayer.x * 0.8 + this->getHalfSize().x * 0.6) &&
		abs(posPlayer.y - this->body.getPosition().y) < (halfSizePlayer.y * 0.8 + this->getHalfSize().y * 0.6));
}

void Meteor::setPosition(sf::Vector2f pos)
{
	this->body.setPosition(pos);
}

sf::Vector2f Meteor::getPosition()
{
	return sf::Vector2f(this->body.getPosition());
}

void Meteor::Update(float deltaTime)
{
	Animation.Update(0, deltaTime);
	this->body.setTextureRect(Animation.uvRect);
}

void Meteor::move(float deltaTime)
{
	this->body.move(sf::Vector2f(deltaTime * -300, deltaTime * 300));
}

sf::Vector2f Meteor::getHalfSize()
{
	sf::Vector2u size = this->body.getTexture()->getSize();
	return sf::Vector2f(size.x / 2, size.y / 2);
}
