#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Animation.h"
#include "meteor.h"
#include <vector>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);//1080 720
    sf::RectangleShape player(sf::Vector2f(216.0f, 180.0f)); //216 180
    player.setPosition(0.0f, 310.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("dragon/dragon_total.png");
    player.setTexture(&playerTexture);

    sf::Sprite bullet;
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("dragon/dragon_total.png");
    bullet.setTexture(bulletTexture);

    /*sf::Sprite meteor;
    sf::Texture meteorTexture;
    meteorTexture.loadFromFile("dragon/meteor.png");
    meteor.setTexture(meteorTexture);
    meteor.setPosition(800.0f, 0.0f);
    meteor.setScale(0.4f, 0.4f);*/

    sf::Texture BackgroundTexture[2];
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("dragon/backgroundtree.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("dragon/backgroundtree.png");
    background[1].setTexture(BackgroundTexture[1]);

    /*std::vector<meteor*> meteors;
    meteors.push_back(new meteor(0.2, 1000, 300, &meteorsTexture));
    meteors.push_back(new meteor(0.2, 500, 300, &meteorsTexture));
    meteors.push_back(new meteor(0.2, 700, 300, &meteorsTexture));*/

    /*meteor* m1 = new meteor(0.2, 1000, 300, sf::Color::Red);
    meteor m2(0.2, 500, 300, sf::Color::Blue);*/


    Animation animation(&playerTexture, sf::Vector2u(4, 6), 0.3f);
    Animation bulletanimation(&bulletTexture, sf::Vector2u(4, 6), 0.3f);
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
         deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        animation.Update(0, deltaTime);
        player.setTextureRect(animation.uvRect);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && player.getPosition().x > -100)
        {
            player.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player.getPosition().x < 800)
        {
            player.move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)&&player.getPosition().y > -30)
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player.getPosition().y < 590)
        {
            player.move(0.0f, 0.1f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            animation.Update(3, deltaTime);
            player.setTextureRect(animation.uvRect);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        for (int i = 0; i < 2; i++) //background
        {
            sf::Vector2f postion = background[i].getPosition();
            background[i].setPosition(postion.x += -0.15f, postion.y);

            if (postion.x <= -3062)
            {
                background[i].setPosition(0, postion.y);
            }
            else if (postion.x >= 0)
            {
                background[i].setPosition(-3062, postion.y);
            }
        }

        /*for (int i = 0; i < meteors.size();i++) {
            meteors[i]->update(-1,0);
            if (meteors[i]->getShape().getPosition().x < 300) {
                delete meteors[i];
                meteors.erase(meteors.begin() + i);
            }
        }*/

        window.clear(sf::Color(240,185,246));
        window.draw(background[0]);
        //window.draw(background1[0]);
        window.draw(player);
        window.draw(bullet);
      /*  for (int i = 0; i < meteors.size();i++) {
            window.draw(meteors[i]->getShape());
        }*/
        window.display();
    }
 
    return 0;


}

