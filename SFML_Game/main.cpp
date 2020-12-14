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
#include "Menu.h"
#include "Enemy.h"



//////////////////////////// chon enemy laew mai pen rai /////////////////////////////////////////////


int main()
{
    int game = 0;
    float HP = 10;
    float HPboss = 20;
    float speed = 1000;
    float y = 0;
    int shoot=false;
    int sc = 0;
    int k = 0;
    sf::RenderWindow window(sf::VideoMode(1080, 720), "DRAGONNN!!!", sf::Style::Close | sf::Style::Resize);//ขนาดจอ
    window.setFramerateLimit(120);

    //////////////////////////////////// LoadFromFile ////////////////////////////////////////////////////////////

    sf::Texture playerTexture; //sprite dragon
    playerTexture.loadFromFile("dragon/dragon_total1.png"); 

    sf::Texture enemybatTexture;
    enemybatTexture.loadFromFile("dragon/enemybat.png");
    sf::Texture enemydragonTexture;
    enemydragonTexture.loadFromFile("dragon/enemydragon.png");

    sf::Texture fireTexture; //sprite fire
    fireTexture.loadFromFile("dragon/fire.png");

    sf::Texture meteorTexture; //sprite meteor
    meteorTexture.loadFromFile("dragon/meteor.png");

    sf::Texture itemPinkTexture; // sprite pink item
    itemPinkTexture.loadFromFile("item/pink.png");
    sf::Texture itemTurboTexture; // sprite turbo item
    itemTurboTexture.loadFromFile("item/turbo.png");
    sf::Texture itemHeartTexture;
    itemHeartTexture.loadFromFile("item/heart.png");

    sf::Texture menuTexture; // menu
    menuTexture.loadFromFile("menu/game.png");
    sf::Texture playTexture;
    playTexture.loadFromFile("menu/play.png");
    sf::Texture howtoTexture;
    howtoTexture.loadFromFile("menu/howto.png");
    sf::Texture highscoreTexture;
    highscoreTexture.loadFromFile("menu/highscore.png");
    sf::Texture exitTexture;
    exitTexture.loadFromFile("menu/exit.png");
    sf::Texture howtoplayTexture;
    howtoplayTexture.loadFromFile("menu/howtoplay.png");
    sf::Texture highscorebgTexture;
    highscorebgTexture.loadFromFile("menu/highscorebg.png");
    sf::Texture backTexture;
    backTexture.loadFromFile("menu/back.png");
    sf::Texture bggameoverTexture;
    bggameoverTexture.loadFromFile("menu/bggameover.png");
    sf::Texture homeTexture;
    homeTexture.loadFromFile("menu/home.png");


    /////////////////////////////////////////////////////////////////////////

    sf::Font scorefont;
    scorefont.loadFromFile("font/joystix.monospace.ttf");

    sf::Text score;
    std::string scoreString;
    score.setFont(scorefont);
    score.setCharacterSize(40);
    score.setFillColor(sf::Color::Black);
    score.setOutlineColor(sf::Color::White);
    score.setPosition(10.0f, 10.0f);

    sf::Text yourscore;
    std::string yourscoreString;
    yourscore.setFont(scorefont);
    yourscore.setCharacterSize(55);
    yourscore.setFillColor(sf::Color::White);
    //yourscore.setOutlineColor(sf::Color::White);
    yourscore.setPosition(130.0f, 480.0f);

    sf::Font namefont;
    namefont.loadFromFile("font/Peach Plum.ttf");

    sf::Text name;
    std::string nameString;
    name.setFont(namefont);
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::Black);
    name.setOutlineColor(sf::Color::White);
    name.setOutlineThickness(0.5f);
    name.setPosition(10.0f, 670.0f);


    ////////////////////////

    float speedBackground = -1.5;
    sf::Texture BackgroundTexture[2]; //background
    sf::Sprite background[2];
    BackgroundTexture[0].loadFromFile("background/backgroundtree.png");
    background[0].setTexture(BackgroundTexture[0]);
    BackgroundTexture[1].loadFromFile("background/backgroundtree.png");
    background[1].setTexture(BackgroundTexture[1]);


    /////////////////////////////////////////////// Sound ////////////////////////////////////////////////////////
    
    sf::SoundBuffer buffer; //sound(shoot)  
    buffer.loadFromFile("sound/sound fire.ogg");
    sf::Sound shoot_sound;
    shoot_sound.setBuffer(buffer);
    sf::Music start_sound; //sound(start)
    start_sound.openFromFile("sound/sound start.ogg");

    ////////////////////////////////////////////////   SET   ////////////////////////////////////////////////////

    Player player(&playerTexture, sf::Vector2u(4, 6), 0.3f, sf::Vector2f(0.0f, 310.0f));

    Item itemPink(&itemPinkTexture, sf::Vector2f(rand() % 6000 + 2000, rand() % 500 + 100));
    Item itemTurbo(&itemTurboTexture, sf::Vector2f(rand() % 6000 + 2500, rand() % 500 + 100));
    Item itemHeart(&itemHeartTexture, sf::Vector2f(rand() % 6000 + 3000, rand() % 500 + 100));

    std::vector<Meteor> meteorlist;
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1400)));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1200)));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1300)));
    meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1400)));
    //meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1200)));
    //meteorlist.push_back(Meteor(&meteorTexture, sf::Vector2u(3, 1), 0.3f, sf::Vector2f(rand() % 2000, -rand() % 1300)));

    std::vector<Enemy> enemylist;
    enemylist.push_back(Enemy(&enemybatTexture, sf::Vector2u(4, 1), 0.3f, sf::Vector2f(1200, rand() % 640 + 20)));
    enemylist.push_back(Enemy(&enemybatTexture, sf::Vector2u(4, 1), 0.3f, sf::Vector2f(1300, rand() % 640 + 20)));
    enemylist.push_back(Enemy(&enemybatTexture, sf::Vector2u(4, 1), 0.3f, sf::Vector2f(1400, rand() % 640 + 20)));
    enemylist.push_back(Enemy(&enemybatTexture, sf::Vector2u(4, 1), 0.3f, sf::Vector2f(1500, rand() % 640 + 20)));

    Enemy boss(&enemydragonTexture, sf::Vector2u(6, 1), 0.3f, sf::Vector2f(1000, rand() % 680 + 20));


    Menu menu(&menuTexture, sf::Vector2f(1, 1), sf::Vector2f(0.0f, 0.0f));
    Menu play(&playTexture, sf::Vector2f(0.6, 0.6), sf::Vector2f(80.0f, 120.0f));
    Menu howto(&howtoTexture, sf::Vector2f(0.6, 0.6), sf::Vector2f(60.0f, 300.0f));
    Menu highscore(&highscoreTexture, sf::Vector2f(0.6, 0.6), sf::Vector2f(80.0f, 480.0f));
    Menu exit(&exitTexture, sf::Vector2f(1, 1), sf::Vector2f(900.0f, 530.0f));
    Menu howtoplay(&howtoplayTexture, sf::Vector2f(1, 1), sf::Vector2f(0.0f, 0.0f));
    Menu hightscorebg(&highscorebgTexture, sf::Vector2f(1, 1), sf::Vector2f(0.0f, 0.0f));
    Menu back(&backTexture, sf::Vector2f(0.6, 0.6), sf::Vector2f(20.0f, 10.0f));
    Menu bggameover(&bggameoverTexture, sf::Vector2f(1, 1), sf::Vector2f(0.0f, 0.0f));
    Menu home(&homeTexture, sf::Vector2f(0.6, 0.6), sf::Vector2f(900.0f, 580.0f));

    Menu heart(&itemHeartTexture, sf::Vector2f(1, 1), sf::Vector2f(580.0f, 0.0f));

    
    int effect = 0;
    double timeEffect = 0;
    Bullet bulletList(&fireTexture, &effect);

    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Event event;
    bulletList.evnt = &event;
    bool isSpacebarPrees = false;
    start_sound.play();

    /////////////////////////////////////// Start ///////////////////////////////////////////////////////////////////

    while (window.isOpen())
    {
        

        /////////////////////////////////////////////////////// menu /////////////////////////////////////////////////////////////
        while (game == 0) { 
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            window.clear();
            nameString = " Napasorn 63010492";
            name.setString(nameString);
            menu.Draw(window);
            play.Draw(window);
            howto.Draw(window);
            highscore.Draw(window);
            exit.Draw(window);
            window.draw(name);
            window.display();

            if (play.getGlobalBounds(window)) {
                play.setScale(sf::Vector2f(0.7f,0.7f));
            }
            else {
                play.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (howto.getGlobalBounds(window)) {
                howto.setScale(sf::Vector2f(0.7f, 0.7f));
            }
            else {
                howto.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (highscore.getGlobalBounds(window)) {
                highscore.setScale(sf::Vector2f(0.7f, 0.7f));
            }
            else {
                highscore.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (exit.getGlobalBounds(window)) {
                exit.setScale(sf::Vector2f(1.1f, 1.1f));
            }
            else { 
                exit.setScale(sf::Vector2f(1.0f, 1.0f));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (play.getGlobalBounds(window)) {
                    game = 1;
                }
                else if (howto.getGlobalBounds(window)) {
                    game = 2;
                }
                else if (highscore.getGlobalBounds(window)) {
                    game = 3;
                }
                else if (exit.getGlobalBounds(window)) {
                    game = 4;
                }
            }
        }

        while (game == 2) {
            howtoplay.Draw(window);
            back.Draw(window);
            window.display();
            if (back.getGlobalBounds(window)) {
                back.setScale(sf::Vector2f(0.7f, 0.7f));
            }
            else {
                back.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& back.getGlobalBounds(window))
            {
                game = 0;
            }
        }

        while (game == 3) { ////////////////////////////////////////////////// ยังไม่เสร็จ //////////////////////////////////////////////////
            hightscorebg.Draw(window);
            back.Draw(window);
            window.display();
            if (back.getGlobalBounds(window)) {
                back.setScale(sf::Vector2f(0.7f, 0.7f));
            }
            else {
                back.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && back.getGlobalBounds(window))
            {
                game = 0;
            }
        }

        while (game == 4) {
            window.close();
        }
        while (game == 5) {
            yourscoreString = " YOURSCORE : " + std::to_string(sc / 10);
            yourscore.setString(yourscoreString);
            bggameover.Draw(window);
            window.draw(yourscore);
            home.Draw(window);
            window.display();
            if (home.getGlobalBounds(window)) {
                home.setScale(sf::Vector2f(0.8, 0.8));
            }
            else {
                home.setScale(sf::Vector2f(0.6f, 0.6f));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (home.getGlobalBounds(window)) {
                    game = 0;
                }
            }
        }

        ////////////////////////////////////////////////////////////// in Game ////////////////////////////////////////////////////////////////

        deltaTime = clock.restart().asSeconds();
        //std::cout << deltaTime;
        //return 0;
        while (game == 1) {

            std::cout << HPboss << std::endl;
            //std::cout << sc << std::endl;
            //std::cout << deltaTime << std::endl;
            sc++;
            //HP = HP - 0.001;
            sf::RectangleShape playerHP(sf::Vector2f(HP * 40, 30));
            playerHP.setFillColor(sf::Color::Red);
            playerHP.setPosition(650, 30);

            scoreString = " SCORE : " + std::to_string(sc/10);
            score.setString(scoreString);

            bulletList.positionPlayer.x = player.getPosition().x + 80 ;
            bulletList.positionPlayer.y = player.getPosition().y + 45;
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
                if (bulletList.canAttack() && effect!=3) { /////////////////////// ตอนเจ็บต้องยิงไม่ได้ ////////////////////
                    player.actionAttack();
                    shoot_sound.play();
                }
            }
            if (event.type == sf::Event::EventType::KeyReleased && isSpacebarPrees == true)
            {
                isSpacebarPrees = false;
                //std::cout << "set isSpacebarPrees: false" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
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

                if (position.x <= -3062) {
                    background[i].setPosition(0, position.y);
                }
                else if (position.x >= 0) {
                    background[i].setPosition(-3062, position.y);
                }
            }

            ////////////////////////////////// item ////////////////////////////////////////////////////////////////////

            if (itemPink.checkColilistion(player.getPosition(), player.getHalfSize())) { //itemPink
                //std::cout << "CHONNNNNNNNNNN" << std::endl;
                itemPink.setPosition(sf::Vector2f(-500, -500));
                effect = 2;
                timeEffect = 10;
                itemPink.reset(-200);
            }

            if (itemTurbo.checkColilistion(player.getPosition(), player.getHalfSize())) { //itemTurbo => 5/11/2020 6.06 PM
                //std::cout << "CHONNNNNNNNNNN" << std::endl;
                itemTurbo.setPosition(sf::Vector2f(-500, -500));
                effect = 3;
                speedBackground = -5.0;
                timeEffect = 5;
                itemTurbo.reset(-200);

            }

            if (itemHeart.checkColilistion(player.getPosition(), player.getHalfSize())) { 
                //std::cout << "CHONNNNNNNNNNN" << std::endl;
                itemHeart.setPosition(sf::Vector2f(-500, -500));
                itemHeart.reset(-200);
                if (HP == 8) {
                    HP = HP + 2;
                }
                if (HP == 9) {
                    HP = HP + 1;
                }
                if (HP <= 7) {
                    HP = HP + 3;
                }
            }

            //////////////////////////////////////// Item Time up ///////////////////////////////////////////////////////////

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

            /////////////////////////////////////////////// meteor checkchon /////////////////////////////////////////////////////////////
            for (int i = 0; i < 4; i++) {
                if ((meteorlist[i].checkColilistion(player.getPosition(), player.getHalfSize())&& effect!=3)) {
                    meteorlist[i].setPosition(sf::Vector2f(-500, -500));
                    player.actionHurt();
                    HP--;
                    
                }
                meteorlist[i].reset(-500.0f);
            }
            if (HP <= 0) {
                game = 5;
            }


            //////////////////////////////////////////////////////////////////////////////////// บัคคคคคคคคคคคคคคคคคคค
            for (int i = 0; i < enemylist.size(); i++) {
                if ((enemylist[i].checkColilistion(player.getPosition(), player.getHalfSize()) && effect != 3)) {
                    enemylist[i].setPosition(sf::Vector2f(-500, -500));
                    player.actionHurt();
                    HP--;
                }
                enemylist[i].reset(-200.0f);
            }
            
            for (int i = 0; i < enemylist.size(); i++) {
                for (int j = 0; j < bulletList.getBulletSize(); j++) {
                    if (enemylist[i].checkColilistion(bulletList.getPosition(j), bulletList.getHalfSize())&&enemylist[i].getPosition().x <= 1080) {
                        enemylist[i].setPosition(sf::Vector2f(-500, -500));
                        sc = sc + 500;
                    }
                    enemylist[i].reset(-200.0f);
                }
            }

            /*for (int j = 0; j < bulletList.getBulletSize(); j++) {
                if (boss.checkColilistion(bulletList.getPosition(j), bulletList.getHalfSize()) && boss.getPosition().x <= 1080) {
                    HPboss=;
                }
                
            }

            if (HPboss <= 0) {
                boss.setPosition(sf::Vector2f(-500, -500));
                boss.reset(-500.0f);
                sc = sc + 5000;
            }*/

            //if (sc <= 10000) {
            //    
            //}

            if (sc >= 30000 && sc < 60000) {
                for (int i = 0; i < enemylist.size(); i++) {
                    enemylist[i].move(deltaTime * 0.5);
                }
                for (int i = 0; i < meteorlist.size(); i++) {
                    meteorlist[i].move(deltaTime * 0.5);
                }
            }

            if (sc >= 60000) {
                for (int i = 0; i < enemylist.size(); i++) {
                    enemylist[i].move(deltaTime * 0.7);
                }
                for (int i = 0; i < meteorlist.size(); i++) {
                    meteorlist[i].move(deltaTime * 0.7);
                }
            }



            ///////////////////////////////////// Draw /////////////////////////////////////////////////////////////
            window.clear(sf::Color(240, 185, 246));
            window.draw(background[0]);
            bulletList.Draw(window);
            player.Draw(window, deltaTime);
            itemPink.Draw(window, deltaTime);
            itemTurbo.Draw(window, deltaTime);
            itemHeart.Draw(window, deltaTime);
            for (Meteor& meteorlist : meteorlist)
                meteorlist.Draw(window, deltaTime);
            for (Enemy& enemylist : enemylist)
                enemylist.Draw(window, deltaTime);
            window.draw(playerHP);
            window.draw(score);
            heart.Draw(window);
           // boss.Draw(window, deltaTime);

            window.display();
        }

    }
    return 0;
}

