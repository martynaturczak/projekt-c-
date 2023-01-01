#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include "map.h"
#include "menu.h"
#include "gameover.h"
#include "ranking.h"
#include "set_nickname_menu.h"

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Game");
    sf::RenderWindow ranking_window(sf::VideoMode(512, 256), "Ranking");
    // sf::RenderWindow gameover_window(sf::VideoMode(512, 256), "GameOver");
    sf::RenderWindow menu_window(sf::VideoMode(512, 256), "Menu");
    Menu menu(menu_window.getSize().x,menu_window.getSize().y);
    sf::View view(sf::Vector2f(256.f, 128.f), sf::Vector2f(512.f, 256.f));
    sf::Vector2f position;
    position.x = 0;
    position.y = 192;

    sf::Clock clock;
    const float timestep = 1.0/60.0;
    float time = 0;

    sf::Font font;
    font.loadFromFile("ARIAL.TTF");
    sf::Text text,text1,text2,text3;
    text.setFont(font);
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    
    sf::Texture texture;
	texture.loadFromFile("player.png");
    sf::Sprite sprite;
	sprite.setTexture(texture);
    sprite.setPosition(position.x,position.y);
    float velocityX = 0, velocityY = 0;
    float gravity = 0.05;
    bool on_ground = 1;
    int column = 64;
    int points = 0;
    string top1,top2,top3;
    int top1_value, top2_value, top3_value;
    int x2 = -1;

    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setFillColor(sf::Color::Yellow);  

    bool isRankingClosed = false; 
    bool isMenuClosed = false;  
    bool isExitPressed = false;  
    // bool isBackToMenuPressed = false;  
     
    const int level[] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 3, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    int level2[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    int level3[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    const int menu_background[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    TileMap map;
    TileMap coin;
    TileMap enemy;
    TileMap menu_bg;
    if (!map.load("set.png", sf::Vector2u(32, 32), level, column, 8))
        return -0;
    if (!coin.load("set2.png", sf::Vector2u(32, 32), level2, column, 8))
        return -1;
    if (!enemy.load("set3.png", sf::Vector2u(32, 32), level3, column, 8))
        return -1;
    if (!menu_bg.load("background.png", sf::Vector2u(32, 32), menu_background, 16, 8))
        return -1;
    while (menu_window.isOpen())
    {
        sf::Event event1;
        while (menu_window.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                menu_window.close();
            if (event1.type == sf::Event::KeyReleased)
            {
                if (event1.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUp();
                    break;
                }
                if (event1.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                    break;
                }
                if (event1.key.code == sf::Keyboard::Return)
                {
                    int x = menu.MenuPressed();
                    if (x == 0)
                    {
                        // isBackToMenuPressed = false;
                        sf::RenderWindow nickname_window(sf::VideoMode(512, 256), "Set nickname");
                        Nickname nick_name(nickname_window.getSize().x,nickname_window.getSize().y);
                        while(nickname_window.isOpen())
                        {
                            sf::Event event;
                            while (nickname_window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    nickname_window.close();
                                if (event.type == sf::Event::TextEntered)
                                {
                                    if(event.text.unicode == 8 and playerInput.getSize() != 0)
                                        playerInput.erase(playerInput.getSize() - 1, playerInput.getSize());
                                    else if((event.text.unicode >= 97 and event.text.unicode <= 122) or  (event.text.unicode >= 65 and event.text.unicode <= 90))
                                        playerInput +=event.text.unicode;
                                    playerText.setString(playerInput);
                                }
                                if (event.type == sf::Event::KeyReleased)
                                {
                                    if (event.key.code == sf::Keyboard::Up)
                                    {
                                        nick_name.MoveUp();
                                        break;
                                    }
                                    if (event.key.code == sf::Keyboard::Down)
                                    {
                                        nick_name.MoveDown();
                                        break;
                                    }
                                    if (event.key.code == sf::Keyboard::Return)
                                    {
                                        x2 = nick_name.NicknamePressed();
                                    }
                                }
                                if(x2 == 0 and playerInput.getSize() != 0)
                                {
                                    nickname_window.close();
                                    break;
                                }
                                else if(x2 == 1)
                                {
                                    // isBackToMenuPressed = true;
                                    nickname_window.close();
                                    x = 0;
                                    break;
                                }
                                // if(isBackToMenuPressed == true)
                                // {
                                //     window.create(sf::VideoMode(512, 256), "Game");
                                //     menu_window.create(sf::VideoMode(512, 256), "Menu");
                                //     x = 0;
                                // }
                            }
                        nickname_window.clear();
                        nickname_window.draw(menu_bg);
                        nick_name.draw(nickname_window);
                        playerText.setPosition(220, 90);
                        nickname_window.draw(playerText);
                        nickname_window.draw(text);
                        nickname_window.display();
                        }
                        while (window.isOpen())
                        {
                            sf::Event event;
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    window.close();
                            }
                            time += clock.restart().asSeconds();
                            while (time >= timestep)
                            {
                                text.setString("Points: " + std::to_string(points));
                                text.setCharacterSize(15);
                                text.setFillColor(sf::Color::Black);
                                time -= timestep;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                                {
                                    if (position.x <= 0)
                                    {
                                        position.x = 0;
                                        velocityX = 0;
                                    }
                                    else
                                        velocityX = -2;
                                }
                                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                                {
                                    velocityX = 2;
                                }
                                else
                                {
                                    velocityX = 0;
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                                {
                                    if (position.y < 0)
                                        velocityY += gravity;
                                    else if (on_ground == 1)
                                    {
                                        velocityY = -2.0;
                                        on_ground = 0;
                                    }
                                }
                                if (position.y < 192)
                                {
                                    velocityY += gravity;
                                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                                    {
                                        velocityX = -1.0;
                                    }
                                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                                    {
                                        velocityX = 1.0;
                                    }
                                }
                                if (position.y > 192)
                                {
                                    velocityX = 0;
                                    velocityY = 0;
                                    position.y = 192;
                                }
                                if (level[(int)(position.y/32) * column + (int)((position.x + 32 + velocityX)/32)] == 2)
                                {
                                    velocityX = 0;
                                }
                                if (level[(int)(position.y/32) * column + (int)((position.x + velocityX)/32)] == 2)
                                {
                                    velocityX = 0;
                                }
                                if (level[(int)((position.y + 32)/32) * column + (int)((position.x + 32 + velocityX)/32)] == 2)
                                {
                                    velocityX = 0;
                                }
                                if (level[(int)((position.y + 32)/32) * column + (int)((position.x + velocityX)/32)] == 2)
                                {
                                    velocityX = 0;
                                }
                                if ((level[(int)((position.y + 32 + velocityY)/32) * column + (int)((position.x + 32)/32)] == 2) or (level[(int)((position.y + 32 + velocityY)/32) * column + (int)((position.x + 32)/32)] == 0))
                                {
                                    velocityY = 0;
                                    on_ground = 1;
                                }
                                if (level[(int)((position.y + 32 + velocityY)/32) * column + (int)(position.x/32)] == 2 or (level[(int)((position.y + 32 + velocityY)/32) * column + (int)((position.x)/32)] == 0))
                                {
                                    velocityY = 0;
                                    on_ground = 1; 
                                } 
                                if (level2[(int)((position.y + 16 )/32) * column  + (int)((position.x + 16)/32)] == 1)
                                {
                                    level2[(int)((position.y + 16)/32) * column + (int)((position.x + 16)/32)] = 0;
                                    points++;
                                    if (!coin.load("set2.png", sf::Vector2u(32, 32), level2, column, 8))
                                        return -1;
                                }
                                if (level[(int)((position.y + 40)/32) * column + (int)((position.x)/32)] == 3)
                                {
                                    ifstream file("zapis.txt");
                                    vector<string>nickname;
                                    vector<int>values1;
                                    if (file.is_open()) 
                                    {
                                        string line;
                                        int number = 0;
                                        while (getline(file, line)) 
                                        {
                                            if (number % 2 == 0)
                                            {
                                                nickname.push_back(line);
                                            }
                                            else if (number % 2 == 1)
                                            {
                                                values1.push_back(std::stoi(line));
                                            } 
                                            number++;
                                        }
                                        file.close();
                                    }
                                    bool t = false;
                                    for (int iter = 0; iter < nickname.size(); iter++)
                                    {
                                        if (nickname[iter] == string(playerInput))
                                        {
                                            t = true;
                                            if (values1[iter] < points)
                                                values1[iter] = points;
                                            break;
                                        }
                                    }
                                    if (t == false)
                                    {
                                        nickname.push_back(playerInput);
                                        values1.push_back(points);
                                    }
                                    ofstream file2("zapis.txt");
                                    for (int iter = 0; iter < nickname.size(); iter++)
                                    {
                                        file2 << nickname[iter] << '\n';
                                        file2 << values1[iter] << '\n';
                                    }
                                    window.close();
                                }
                                //enemy
                                if (level3[(int)((position.y + 32)/32) * column + (int)((position.x)/32)] == 1)
                                {
                                    level3[(int)((position.y + 32)/32) * column + (int)((position.x)/32)] = 0;
                                    if (!enemy.load("set3.png", sf::Vector2u(32, 32), level3, column, 8))
                                        return -1;
                                }
                                if (level3[(int)(position.y/32) * column + (int)((position.x + 32 + velocityX)/32)] == 1)
                                {
                                    velocityX = 0;
                                    if (points > 0)
                                        points--;
                                }
                                if (level3[(int)(position.y/32) * column + (int)((position.x + velocityX)/32)] == 1)
                                {
                                    velocityX = 0;
                                    if (points > 0)
                                        points--;
                                }
                                if (level3[(int)((position.y + 32)/32) * column + (int)((position.x + 32 + velocityX)/32)] == 1)
                                {
                                    velocityX = 0;
                                    if (points > 0)
                                        points--;
                                }
                                if (level3[(int)((position.y + 32)/32) * column + (int)((position.x + velocityX)/32)] == 1)
                                {
                                    velocityX = 0;
                                    if (points > 0)
                                        points--;
                                }
                                position.x += velocityX;
                                position.y += velocityY;
                                view.move(velocityX, 0);
                            }
                            ranking_window.close();
                            menu_window.close();
                            window.clear();
                            window.setView(view);
                            sprite.setPosition(position.x, position.y);
                            window.draw(map);
                            window.draw(coin);
                            window.draw(enemy);
                            window.draw(sprite);
                            text.setPosition(position.x, 0);
                            window.draw(text);
                            window.display();
                        }
                    }
                    if (x == 1)
                    {
                        isExitPressed = false; 
                        isMenuClosed = false; 
                        if (isRankingClosed == true)
                        {
                            ranking_window.create(sf::VideoMode(512, 256), "Ranking");   
                        }
                        Ranking ranking(ranking_window.getSize().x,ranking_window.getSize().y);
                        while (ranking_window.isOpen())
                        {
                            text1.setString(top1 + " " + std::to_string(top1_value));
                            text1.setFillColor(sf::Color::Yellow);    
                            text1.setPosition(180,90);  
                            text1.setCharacterSize(30);
                            text1.setStyle(sf::Text::Italic);

                            text2.setString(top2 + " " + std::to_string(top2_value));
                            text2.setFillColor(sf::Color::Yellow);      
                            text2.setPosition(180,130);  
                            text2.setCharacterSize(30);
                            text2.setStyle(sf::Text::Italic);

                            text3.setString(top3 + " " + std::to_string(top3_value));
                            text3.setFillColor(sf::Color::Yellow);      
                            text3.setPosition(180,170);  
                            text3.setCharacterSize(30);
                            text3.setStyle(sf::Text::Italic);
                            sf::Event event2;
                            while (ranking_window.pollEvent(event2))
                            {
                                if (event2.type == sf::Event::Closed)
                                    ranking_window.close();
                                if (event2.type == sf::Event::KeyReleased)
                                {
                                    if (event2.key.code == sf::Keyboard::Up)
                                    {
                                        ranking.MoveUp();
                                        break;
                                    }
                                    if (event2.key.code == sf::Keyboard::Down)
                                    {
                                        ranking.MoveDown();
                                        break;
                                    }
                                    if (event2.key.code == sf::Keyboard::Return)
                                    {
                                        int x2 = ranking.RankingPressed();
                                        if (x2 == 0)
                                        {
                                            isRankingClosed = true;
                                            isMenuClosed = true;
                                            ranking_window.close();
                                        }
                                        if (x2 == 1)
                                        {
                                            ranking_window.close();
                                            isExitPressed = true;
                                            menu_window.close();
                                            break;
                                        }
                                        break;
                                    }
                                } 
                                ifstream file("zapis.txt");
                                vector<string>nickname;
                                vector<int>values1;
                                vector<int>values2;
                                if (file.is_open()) 
                                {
                                    string line;
                                    int number = 0;
                                    while (getline(file, line)) 
                                    {
                                        if (number % 2 == 0)
                                        {
                                            nickname.push_back(line);
                                        }
                                        else if (number % 2 == 1)
                                        {
                                            values1.push_back(std::stoi(line));
                                            values2.push_back(std::stoi(line));
                                        } 
                                        number++;
                                    }
                                    
                                    file.close();
                                }
                                sort (values1.begin(), values1.end());
                                for (int i = 0; i < values2.size(); i++)
                                {
                                    if (values1[values2.size()-1] == values2[i])
                                    {
                                        top1 = nickname[i];
                                        top1_value = values1[values2.size()-1];
                                    }
                                    if (values1[values2.size()-2] == values2[i])
                                    {
                                        top2 = nickname[i];
                                        top2_value = values1[values2.size()-2];
                                    }
                                    if (values1[values2.size()-3] == values2[i])
                                    {
                                        top3 = nickname[i];
                                        top3_value = values1[values2.size()-3];
                                    }
                                }
                            }
                        menu_window.close(); 
                        window.close();
                        ranking_window.clear();
                        ranking_window.draw(menu_bg);
                        ranking.draw(ranking_window);
                        ranking_window.draw(text1);
                        ranking_window.draw(text2);
                        ranking_window.draw(text3);
                        ranking_window.display();
                        }
                    if(isMenuClosed == true)
                    {
                        window.create(sf::VideoMode(512, 256), "Game");
                        menu_window.create(sf::VideoMode(512, 256), "Menu");
                        x = 0;
                    }
                    }
                    if (x == 2)
                    {
                        menu_window.close();
                        isExitPressed = true;
                    }
                    break;
                }
            }
        }
    menu_window.clear();
    menu_window.draw(menu_bg);
    menu.draw(menu_window);
    menu_window.display();
    }
    sf::RenderWindow gameover_window(sf::VideoMode(512, 256), "GameOver");
    GameOver game_over(gameover_window.getSize().x,gameover_window.getSize().y);
    if(isExitPressed == true)
    {
        gameover_window.close();
    }
    while (gameover_window.isOpen())
    {
        sf::Event event3;
        while (gameover_window.pollEvent(event3))
        {
            text.setString(std::to_string(points));
            text.setFillColor(sf::Color::Yellow);    
            text.setFont(font);  
            text.setPosition(280,100);  
            text.setCharacterSize(25);
            text.setStyle(sf::Text::Italic);
            if (event3.type == sf::Event::Closed)
                gameover_window.close();
            if (event3.type == sf::Event::KeyReleased)
            {
                if (event3.key.code == sf::Keyboard::Up)
                {
                    game_over.MoveUp();
                    break;
                }
                if (event3.key.code == sf::Keyboard::Down)
                {
                    game_over.MoveDown();
                    break;
                }
                if (event3.key.code == sf::Keyboard::Return)
                {
                    int x1 = game_over.GameOverPressed();
                    if (x1 == 0)
                    {
                        gameover_window.close();
                        while (ranking_window.isOpen())
                        {
                            sf::Event event2;
                            while (ranking_window.pollEvent(event2))
                            {
                                if (event2.type == sf::Event::Closed)
                                    ranking_window.close();
                            }
                        menu_window.close(); 
                        window.close();
                        ranking_window.clear();
                        ranking_window.display();
                        }
                    }
                    if (x1 == 1)
                        gameover_window.close();
                    break;
                }
            }       
        }
    gameover_window.clear();
    gameover_window.draw(menu_bg);
    game_over.draw(gameover_window);
    gameover_window.draw(text);
    gameover_window.display();
    }
}