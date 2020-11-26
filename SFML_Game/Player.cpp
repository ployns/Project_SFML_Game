#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position):
	Animation(texture, imageCount, switchTime)
{
	this->body.setSize(sf::Vector2f(216.0f, 180.0f));
    //this->body.setSize(sf::Vector2f(180.0f, 80.0f));
	this->body.setPosition(position);
	this->body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow& window, float _deltatime)
{
	//this->update();
    this->update(_deltatime);
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
    if (state != 4) {
        this->state = 3;
    }
}

void Player::actionTurbo()
{
    this->state = 1;
}

void Player::actionHurt()
{
    this->state = 4;
}


sf::Vector2f Player::getHalfSize()
{
    sf::Vector2u size = this->body.getTexture()->getSize();
    return sf::Vector2f(size.x / 4 / 2, size.y / 6 / 2);
}

void Player::update(float deltaTime)
{
   // this->deltaTime = this->clock.restart().asSeconds();
    if (this->Animation.Update(this->state, deltaTime) == true) 
    {
        this->state = 0;
    }
    this->body.setTextureRect(this->Animation.uvRect);
}

void Player::controller()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getPosition().x > -100)
    {
        this->body.move(-1.5f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getPosition().x < 800)
    {
        this->body.move(1.5f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getPosition().y > -30)
    {
        this->body.move(0.0f, -1.5f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getPosition().y < 590)
    {
        this->body.move(0.0f, 1.5f);
    }
}
