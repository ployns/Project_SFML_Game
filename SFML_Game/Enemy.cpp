#include "Enemy.h"

///////////////////////////////////// copy meteor ////////////////////////////////////////////////////


Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f scale) :
	Animation(texture, imageCount, switchTime)
{
	this->body.setScale(scale);
	this->body.setPosition(position);
	this->body.setTexture(*texture);

	//this->shape.setPosition(this->body.getPosition().x + 25, this->body.getPosition().y + 15);
	//this->shape.setSize(sf::Vector2f(100,50));

	//this->shape.setFillColor(sf::Color::Transparent);
	//this->shape.setOutlineThickness(1);
	//this->shape.setOutlineColor(sf::Color::Red);
	

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
		//window.draw(this->shape);

	}
}

bool Enemy::checkColilistion(sf::Vector2f posPlayer, sf::Vector2f halfSizePlayer)
{
	/*std::cout << abs(posPlayer.x - this->body.getPosition().x) << " " << (halfSizePlayer.x * 0.5 + this->getHalfSize().x * 0.5) << " " <<
		abs(posPlayer.y - this->body.getPosition().y) << " " << (halfSizePlayer.y * 0.8 + this->getHalfSize().y * 0.8) << std::endl;*/
	return (abs(posPlayer.x - this->body.getPosition().x) < (halfSizePlayer.x * 0.5 + this->getHalfSize().x * 0.5) &&
		abs(posPlayer.y - this->body.getPosition().y) < (halfSizePlayer.y * 0.8 + this->getHalfSize().y * 0.8));
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
		this->body.setPosition(sf::Vector2f(1200, rand() % 640 + 20 ));
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
