#include "Fire.h"

Fire::Fire(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
	Animation(texture,imageCount, switchTime)
{
	this->fire.setScale(sf::Vector2f(1,1));
	this->fire.setPosition(position);
	this->fire.setTexture(*texture);

}

Fire::~Fire()
{

}

void Fire::Update(float deltaTime)
{
	Animation.Update(5, deltaTime);
	fire.setTextureRect(Animation.uvRect);
}
void Fire::Draw(sf::RenderWindow& window)
{
	window.draw(fire);
}
