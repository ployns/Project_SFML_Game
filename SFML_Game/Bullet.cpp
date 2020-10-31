#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture)
{
    for (int i = 0; i < fire_num; i++) {
        Fire fire(texture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(100, 100));
        fires.push_back(fire);
    }
}

Bullet::~Bullet()
{
}

void Bullet::Draw(sf::RenderWindow& window)
{
    deltaTime = clock.restart().asSeconds();
    this->action();
    for (int i = 0; i < fire_num; i++)
    {
        if (fires[i].isActive() == true)
        {
            //std::cout << "Do" << std::endl;
            fires[i].Draw(window);
            fires[i].Update(deltaTime);
        }
    }
}

bool Bullet::canAttack()
{
    for (int i = 0; i < fire_num; i++)
    {
        if (this->fires[i].isActive() == false) {
            return true;
        }
    }
    return false;
}

void Bullet::action()
{
    if ((*this->evnt).type == sf::Event::EventType::TextEntered
        and (*this->evnt).text.unicode == ' '
        and this->isSpacebarPrees == false)
    {
        //std::cout << "set isSpacebarPrees: true" << std::endl;
        this->isSpacebarPrees = true;
        for (int i = 0; i < fire_num; i++)
        {
            if (this->fires[i].isActive() == false) {
                //this->fires[i].setPosition(sf::Vector2f(300.0f,300.0f)); => fixed : 31/10/20 12.20AM.
                fires[i].setPosition(this->positionPlayer);
                this->fires[i].setActive(true);
                //std::cout << "fire [" << i << "]" << std::endl;
                //std::cout << fires[i].getPosition().x << std::endl;
                break;
            }
        }
    }
    if ((*this->evnt).type == sf::Event::EventType::KeyReleased && this->isSpacebarPrees == true)
    {
        this->isSpacebarPrees = false;
       // std::cout << "set isSpacebarPrees: false" << std::endl;
    }
    
}
