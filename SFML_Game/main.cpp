#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Animation.h"
#include "meteor.h"
#include <vector>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape player(sf::Vector2f(216.0f, 180.0f)); //216 180
    player.setPosition(0.0f, 310.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("dragon/dragon_total.png");
    player.setTexture(&playerTexture);
    


    sf::Texture BackgroundTexture[2];
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("dragon/backgroundsky2.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("dragon/backgroundsky2.png");
    background[1].setTexture(BackgroundTexture[1]);

    sf::Texture BackgroundTexture1[2];
    sf::Sprite background1[2];
    BackgroundTexture1[0].loadFromFile("dragon/backgroundtown.png");
    background1[0].setTexture(BackgroundTexture1[0]);
    BackgroundTexture1[1].loadFromFile("dragon/backgroundtown.png");
    background1[1].setTexture(BackgroundTexture1[1]);

    std::vector<meteor*> meteors;
    //meteors.push_back(new meteor(0.2, 1000, 300, sf::Color::Red));
   // meteors.push_back(new meteor(0.2, 500, 300, sf::Color::Blue));
    //meteors.push_back(new meteor(0.2, 700, 300, sf::Color::Green));
    /*meteor* m1 = new meteor(0.2, 1000, 300, sf::Color::Red);
    meteor m2(0.2, 500, 300, sf::Color::Blue);*/


    Animation animation(&playerTexture, sf::Vector2u(4, 6), 0.3f);
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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
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

        for (int i = 0; i < 2; i++)
        {
            sf::Vector2f postion = background[i].getPosition();
            background[i].setPosition(postion.x += -0.05f, postion.y);

            if (postion.x <= -3062)
            {
                background[i].setPosition(0, postion.y);
            }
            else if (postion.x >= 0)
            {
                background[i].setPosition(-3062, postion.y);
            }
        }

        for (int i = 0; i < 2; i++)
        {
            sf::Vector2f postion = background1[i].getPosition();
            background1[i].setPosition(postion.x += -0.2f, postion.y);

            if (postion.x <= -3062)
            {
                background1[i].setPosition(0, postion.y);
            }
            else if (postion.x >= 0)
            {
                background1[i].setPosition(-3062, postion.y);
            }
        }
        /*f (m1 != NULL) {
            m1->update(-1, 0.0);
            if (m1->getShape().getPosition().x <= 300) {
                delete m1;
            }
        }*/
        for (int i = 0; i < meteors.size();i++) {
            meteors[i]->update(-1,0);
            if (meteors[i]->getShape().getPosition().x < 300) {
                delete meteors[i];
                meteors.erase(meteors.begin() + i);
            }
        }

        window.clear(sf::Color(240,185,246));
        window.draw(background[0]);
        window.draw(background1[0]);
        window.draw(player);

        //for (int i = 0; i < meteors.size();i++) {
        //    window.draw(meteors[i]->getShape());
        //}
        window.display();
    }
 
    return 0;


}

