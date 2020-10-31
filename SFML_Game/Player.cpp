#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position):
	Animation(texture, imageCount, switchTime)
{
	this->body.setSize(sf::Vector2f(216.0f, 180.0f));
	this->body.setPosition(position);
	this->body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow& window)
{
	this->update();
	window.draw(body);
    this->controller();
	//std::cout << this->getPosition().x << std::endl; 
}

sf::Vector2f Player::getPosition()
{
	return this->body.getPosition();
}

void Player::actionAttack()
{
    this->state = 3;
}

void Player::update()
{
    this->deltaTime = this->clock.restart().asSeconds();
    if (this->Animation.Update(this->state, this->deltaTime) == true) 
    {
        this->state = 0;
    }
    this->body.setTextureRect(this->Animation.uvRect);
   
}

void Player::controller()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getPosition().x > -100)
    {
        this->body.move(-0.1f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getPosition().x < 800)
    {
        this->body.move(0.1f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getPosition().y > -30)
    {
        this->body.move(0.0f, -0.1f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getPosition().y < 590)
    {
        this->body.move(0.0f, 0.1f);
    }
}
