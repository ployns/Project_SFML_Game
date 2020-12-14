#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, int* effect)
{
    this->effect = effect;
    for (int i = 0; i < fire_num; i++) {
        Fire fire(texture, sf::Vector2u(4, 1), 0.3f, sf::Vector2f(100, 100));
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
            //std::cout << *this->effect << std::endl;
            
            fires[i].Update(deltaTime);
            fires[i].Draw(window);

            if (fires[i].getDeltaDistance() > 200 && fires[i].getEffect() == 1) {
                fires[i].setEffect(0);
                fires[i + 1].setEffect(0);
                fires[i + 2].setEffect(0);
                fires[i].setY(-50);
                fires[i+1].setY(+50);
                i += 3;
            }
        }
    }
}

int Bullet::getBulletSize()
{
    return this->fire_num;
}

sf::Vector2f Bullet::getPosition(int idex)
{
    if (idex >= 0 and idex <= fire_num) {
        return this->fires[idex].getPosition();
    }
}


sf::Vector2f Bullet::getHalfSize()
{
    for (int i = 0; i < fire_num; i++) {
        return this->fires[i].getHalfSize();
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
                
                //std::cout << "fire [" << i << "]" << std::endl;
                //std::cout << fires[i].getPosition().x << std::endl;
                switch (*this->effect)
                {
                case 0:
                    fires[i].setPosition(this->positionPlayer);
                    this->fires[i].setActive(true);
                    break;
                case 2:
                    fires[i].setPosition(sf::Vector2f(this->positionPlayer.x, this->positionPlayer.y-50));
                    fires[i + 1].setPosition(sf::Vector2f(this->positionPlayer.x+30, this->positionPlayer.y));
                    fires[i + 2].setPosition(sf::Vector2f(this->positionPlayer.x, this->positionPlayer.y+50));
                    this->fires[i].setActive(true);
                    this->fires[i + 1].setActive(true);
                    this->fires[i + 2].setActive(true);
                    break;
                default:
                    break;
                }
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
