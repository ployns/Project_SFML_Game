#include "Enemy.h"

///////////////////////////////////// copy meteor ////////////////////////////////////////////////////


Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
	Animation(texture, imageCount, switchTime)
{
	this->body.setScale(sf::Vector2f(1.5, 1.5));
	this->body.setPosition(position);
	this->body.setTexture(*texture);

	//this->Update(deltaTime);
}

Enemy::~Enemy()
{
}

void Enemy::Draw(sf::RenderWindow& window, float _deltatime)
{
	//std::cout << "Do" << std::endl;
	//deltaTime = clock.restart().asSeconds();
	//std::cout << deltaTime;
	//std::cout << this->body.getPosition().x << " " << this->body.getPosition().y << std::endl;
	if (this->body.getPosition().x > -500) {
		//std::cout << "Do" << std::endl;
		window.draw(body);
		this->Update(_deltatime);
		this->move(_deltatime);
	}
}

bool Enemy::checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer)
{
	return (abs(posPlayer.x - this->body.getPosition().x) < (halfSizePlayer.x * 0.5 + this->getHalfSize().x * 0.5) &&
		abs(posPlayer.y - this->body.getPosition().y) < (halfSizePlayer.y * 0.5 + this->getHalfSize().y * 0.5));
}

void Enemy::setPosition(sf::Vector2f pos)
{
	this->body.setPosition(pos);
}

sf::Vector2f Enemy::getPosition()
{
	return (this->body.getPosition());
}

void Enemy::Update(float deltaTime)
{
	Animation.Update(0, deltaTime);
	this->body.setTextureRect(Animation.uvRect);
}

void Enemy::reset(float pos)
{
	if (this->body.getPosition().x <= pos) {
		this->body.setPosition(sf::Vector2f(1200, rand() % 640 + 20));
	}
}

void Enemy::move(float deltaTime)
{
	this->body.move(sf::Vector2f(deltaTime * -250, deltaTime * 0)); //////////////////////(200-rand()%350 )/////////////////
}

sf::Vector2f Enemy::getHalfSize()
{
	sf::Vector2u size = this->body.getTexture()->getSize();
	return sf::Vector2f(size.x / 4 / 2, size.y / 2);
}
