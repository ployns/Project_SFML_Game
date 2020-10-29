#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "meteor.h"
#include "Fire.h"
#include <vector>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);//ขนาดจอ
    sf::RectangleShape player(sf::Vector2f(216.0f, 180.0f)); //ขนาดมังกร
    player.setPosition(0.0f, 310.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("dragon/dragon_total.png"); //sprite dragon
    player.setTexture(&playerTexture);

    //sf::Sprite bullet;
    //sf::Texture bulletTexture;
    //bulletTexture.loadFromFile("dragon/dragon_total.png"); //sprite bullet
    //bullet.setTexture(bulletTexture);

    sf::Texture fireTexture;
    fireTexture.loadFromFile("dragon/dragon_total.png");
    std::vector<Fire> fires;
 

    sf::Texture BackgroundTexture[2]; //background
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("dragon/backgroundtree.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("dragon/backgroundtree.png");
    background[1].setTexture(BackgroundTexture[1]);

    sf::SoundBuffer buffer;
    buffer.loadFromFile("dragon/sound fire.ogg");
    sf::Sound shoot_sound;
    shoot_sound.setBuffer(buffer);

    sf::Music start_sound;
    start_sound.openFromFile("dragon/sound start.ogg");


    /*std::vector<meteor*> meteors;
    meteors.push_back(new meteor(0.2, 1000, 300, &meteorsTexture));
    meteors.push_back(new meteor(0.2, 500, 300, &meteorsTexture));
    meteors.push_back(new meteor(0.2, 700, 300, &meteorsTexture));*/

    Fire fire(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(100, 100));

    Animation animation(&playerTexture, sf::Vector2u(4, 6), 0.3f); //ตัดช่องของมังกร


    float deltaTime = 0.0f;
    sf::Clock clock;

    start_sound.play();

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
        for (Fire& fire : fires)
            fire.Update(deltaTime);
        fire.Update(deltaTime);
        fire.Draw(window);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player.getPosition().y > -30)
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player.getPosition().y < 590)
        {
            player.move(0.0f, 0.1f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            shoot_sound.play();
            animation.Update(3, deltaTime);
            player.setTextureRect(animation.uvRect);
            fires.push_back(Fire(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(player.getPosition().x , player.getPosition().y)));
            //Fire fire(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(player.getPosition().x, player.getPosition().y));
            fire.Update(deltaTime);
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        for (int i = 0; i < 2; i++) //background loop
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
        window.draw(player);
        //for (Fire& fire : fires)
        fire.Draw(window);
        /*fire.Draw(window);*/
      /*  for (int i = 0; i < meteors.size();i++) {
            window.draw(meteors[i]->getShape());
        }*/
        window.display();
    }
 
    return 0;


}

