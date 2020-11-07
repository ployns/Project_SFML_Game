#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include <vector>
#include "Bullet.h"
#include "Item.h"
#include "Meteor.h"

int main()
{
    float speed = 1000;
    float y = 0;
    int shoot=false;
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);//ขนาดจอ
    window.setFramerateLimit(120 );
    
    //////////////////////////////////// LoadFromFile ////////////////////////////////////////////////////////////

    sf::Texture playerTexture; //sprite dragon
    playerTexture.loadFromFile("dragon/dragon_total.png"); 
    Player player(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(0.0f, 310.0f));

    sf::Texture fireTexture; //sprite fire
    fireTexture.loadFromFile("dragon/dragon_total.png");

    int effect = 0;
    double timeEffect = 0;
    Bullet bulletList(&playerTexture, &effect);

    sf::Texture meteorTexture; //sprite meteor
    meteorTexture.loadFromFile("dragon/meteor.png");
    std::vector<Meteor> meteorlist;
    //Meteor meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(900.0f, -100.0f));
    //Meteor meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(1000.0f, -100.0f));
    //Meteor meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(1200.0f, -300.0f));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(900.0f, -100.0f)));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(1000.0f, -100.0f)));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(1200.0f, -300.0f)));

    sf::Texture itemGreenTexture; // sprite green item
    itemGreenTexture.loadFromFile("dragon/green.png");
    Item itemGreen(&itemGreenTexture, sf::Vector2f(2000.0f, 200.0f));
    sf::Texture itemPinkTexture; // sprite pink item
    itemPinkTexture.loadFromFile("dragon/pink.png");
    Item itemPink(&itemPinkTexture, sf::Vector2f(5000.0f, 400.0f));
    sf::Texture itemTurboTexture; // sprite pink item
    itemTurboTexture.loadFromFile("dragon/turbo.png");
    Item itemTurbo(&itemTurboTexture, sf::Vector2f(8000.0f, 100.0f));

    float speedBackground = -1.5;
    sf::Texture BackgroundTexture[2]; //background
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("dragon/backgroundtree.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("dragon/backgroundtree.png");
    background[1].setTexture(BackgroundTexture[1]);

    

    /////////////////////////////////////////////// Sound ////////////////////////////////////////////////////////
    
    sf::SoundBuffer buffer; //sound(shoot)
    buffer.loadFromFile("dragon/sound fire.ogg");
    sf::Sound shoot_sound;
    shoot_sound.setBuffer(buffer);
    sf::Music start_sound; //sound(start)
    start_sound.openFromFile("dragon/sound start.ogg");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Animation animation(&playerTexture, sf::Vector2u(4, 6), 0.3f); //ตัดช่องของมังกร

    float deltaTime = 0.0f;
    sf::Clock clock;
    start_sound.play();
    sf::Event event;
    bulletList.evnt = &event;
    bool isSpacebarPrees = false;

    /////////////////////////////////////// Start ///////////////////////////////////////////////////////////////////

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

        for (int i = 0; i < 2; i++) //background loop
        {
            sf::Vector2f position = background[i].getPosition();
            background[i].setPosition(position.x += speedBackground, position.y);

            if (position.x <= -3062){
                background[i].setPosition(0, position.y);
            }
            else if (position.x >= 0){
                background[i].setPosition(-3062, position.y);
             }
        }
        ////////////////////////////////// item ////////////////////////////////////////////////////////////////////
        if (itemGreen.checkColilistion(player.getPosition(), player.getHalfSize())) { //itemGreen
            std::cout << "CHONNNNNNNNNNN" << std::endl;
            itemGreen.setPosition(sf::Vector2f(-500, -500));
            effect = 1;
            timeEffect = 10;
        }
        if (itemPink.checkColilistion(player.getPosition(), player.getHalfSize())) { //itemPink
            std::cout << "CHONNNNNNNNNNN" << std::endl;
            itemPink.setPosition(sf::Vector2f(-500, -500));
            effect = 2;
            timeEffect = 10;
        }
        if (itemTurbo.checkColilistion(player.getPosition(), player.getHalfSize())) { //itemTurbo => 5/11/2020 6.06 PM
            std::cout << "CHONNNNNNNNNNN" << std::endl;
            itemTurbo.setPosition(sf::Vector2f(-500, -500));
            effect = 3;
            speedBackground = -5.0;
            timeEffect = 5;
        }

        //////////////////////////////////////// Item Time up ///////////////////////////////////////////////////////////
        if (effect == 1 && timeEffect > 0) {
            timeEffect -= deltaTime;
            //std::cout << timeEffect << std::endl;
            if (timeEffect < 0) {
                effect = 0;
            }
        }
        if (effect == 2 && timeEffect > 0) {
            timeEffect -= deltaTime;

            if (timeEffect < 0) {
                effect = 0;
            }
        }
        if (effect == 3 && timeEffect > 0) {
            timeEffect -= deltaTime;
            player.actionTurbo();
            //std::cout << timeEffect << std::endl;
            if (timeEffect < 0) {
                effect = 0;
                speedBackground = -1.5;
            }
        }

        ///////////////////////////////////// Draw /////////////////////////////////////////////////////////////
        window.clear(sf::Color(240,185,246));
        window.draw(background[0]);
        bulletList.Draw(window);
        player.Draw(window);
        itemGreen.Draw(window);
        itemPink.Draw(window);
        itemTurbo.Draw(window);
        //meteorlist.Draw(window);
        window.display();
    }
    return 0;
}

