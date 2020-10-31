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
	Animation.Update(5, deltaTime);
	body.setTextureRect(Animation.uvRect);
}

void Fire::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Fire::setActive(bool status)
{
	this->active = status;
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

void Fire::move(float deltaTime)
{
	
	if (this->body.getPosition().x > 900) // 
	{
		this->setActive(false);
	}
	else
	{
		//std::cout << "Move" << std::endl;
		this->body.move(sf::Vector2f(deltaTime*1000, 0));
	}
}



