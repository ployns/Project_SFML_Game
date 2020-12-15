#include "Fire.h"

Fire::Fire(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
	Animation(texture,imageCount, switchTime)
{
	this->body.setScale(sf::Vector2f(1,1));
	this->body.setPosition(position);
	this->body.setTexture(*texture);

}

Fire::~Fire()
{

}

void Fire::Update(float deltaTime)
{
	//std::cout << deltaTime << std::endl;
	this->move(deltaTime);
	Animation.Update(0, deltaTime);
	this->body.setTextureRect(Animation.uvRect);
}

void Fire::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Fire::setActive(bool status)
{
	this->active = status;
	if (status == true) {
		startPosition = this->body.getPosition().x;
	}

}

bool Fire::isActive()
{
	return this->active;
}

void Fire::setPosition(sf::Vector2f posi)
{
	this->body.setPosition(posi);
}

sf::Vector2f Fire::getPosition()
{
	return this->body.getPosition();
}

void Fire::setY(double y)
{
	this->body.setPosition(sf::Vector2f(this->body.getPosition().x, this->body.getPosition().y+y));
}

void Fire::setScale(sf::Vector2f scale)
{
	body.setScale(scale);
}

sf::Vector2f Fire::getHalfSize()
{
	sf::Vector2u size = this->body.getTexture()->getSize();
	return sf::Vector2f(size.x /4/ 2, size.y / 2);
}

double Fire::getDeltaDistance()
{
	return this->body.getPosition().x - this->startPosition;
}

void Fire::setEffect(int state)
{
	if (this->effect == 1 && state == 0) {
		this->speed = this->baseSpeed;
	}
	else if (this->effect == 0 && state == 1) {
		this->speed = 0.5;
	}
	this->effect = state;
}

int Fire::getEffect()
{
	return this->effect;
}

void Fire::move(float deltaTime)
{
	
	if (this->body.getPosition().x > 1000) 
	{
		this->setActive(false);
		this->body.setPosition(sf::Vector2f(-3000, -4000));
	}
	else
	{
		//std::cout << "Move" << std::endl;
		this->body.move(sf::Vector2f(this->speed, 0));
	}
}



