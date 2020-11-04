#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include <vector>
#include "Bullet.h"
#include "Item.h"

int main()
{
    int shoot=false;
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);//ขนาดจอ
    sf::Texture playerTexture;
    playerTexture.loadFromFile("dragon/dragon_total.png"); //sprite dragon
    Player player(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(0.0f, 310.0f));

    sf::Texture fireTexture; //sprite fire
    fireTexture.loadFromFile("dragon/dragon_total.png");


    sf::Texture itemGreenTexture;
    itemGreenTexture.loadFromFile("dragon/green.png");
    Item itemGreen(&itemGreenTexture, sf::Vector2f(2000.0f, 310.0f));
    

    Bullet bulletList(&playerTexture);

    sf::Texture BackgroundTexture[2]; //background
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("dragon/backgroundtree.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("dragon/backgroundtree.png");
    background[1].setTexture(BackgroundTexture[1]);

    sf::SoundBuffer buffer; //sound(shoot)
    buffer.loadFromFile("dragon/sound fire.ogg");
    sf::Sound shoot_sound;
    shoot_sound.setBuffer(buffer);

    sf::Music start_sound; //sound(start)
    start_sound.openFromFile("dragon/sound start.ogg");


    Animation animation(&playerTexture, sf::Vector2u(4, 6), 0.3f); //ตัดช่องของมังกร

    float deltaTime = 0.0f;
    sf::Clock clock;
    start_sound.play();
    sf::Event event;
    bulletList.evnt = &event;
    bool isSpacebarPrees = false;
    while (window.isOpen())
    {
        //ส่ง positionPlayer ไปยัง bulletList
        bulletList.positionPlayer = player.getPosition();
        deltaTime = clock.restart().asSeconds();
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        if (event.type == sf::Event::EventType::TextEntered 
            and event.text.unicode == ' '
            and isSpacebarPrees == false)
        {
            //std::cout << "set isSpacebarPrees: true" << std::endl;
            isSpacebarPrees = true;
            if (bulletList.canAttack()) {
                player.actionAttack();
                shoot_sound.play();
            }
        }
        if (event.type == sf::Event::EventType::KeyReleased && isSpacebarPrees == true)
        {
            isSpacebarPrees = false;
            //std::cout << "set isSpacebarPrees: false" << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        itemGreen.move(deltaTime);
        

        for (int i = 0; i < 2; i++) //background loop
        {
            sf::Vector2f position = background[i].getPosition();
            background[i].setPosition(position.x += -0.15f, position.y);

            if (position.x <= -3062)
            {
                background[i].setPosition(0, position.y);
            }
            else if (position.x >= 0)
            {
                background[i].setPosition(-3062, position.y);
            }
        }
        window.clear(sf::Color(240,185,246));
        window.draw(background[0]);
        bulletList.Draw(window);
        player.Draw(window);
        itemGreen.Draw(window);
        window.display();
    }
 
    return 0;


}

