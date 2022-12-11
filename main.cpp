#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "map.h"
#include "menu.h"
#include "gameover.h"

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Game");
    sf::RenderWindow ranking(sf::VideoMode(512, 256), "Ranking");
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
    sf::Text text;
    text.setFont(font);
    
    sf::Texture texture;
	texture.loadFromFile("player.png");
    sf::Sprite sprite;
	sprite.setTexture(texture);
    sprite.setPosition(position.x,position.y);
    float velocityX = 0, velocityY = 0;
    float gravity = 0.05;
    bool on_ground = 1;
    int column = 64;
    int playagain = 0;
    int points = 0;

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
                            ranking.close();
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
                        while (ranking.isOpen())
                        {
                            sf::Event event2;
                            while (ranking.pollEvent(event2))
                            {
                                if (event2.type == sf::Event::Closed)
                                    ranking.close();
                            }
                        menu_window.close(); 
                        window.close();
                        ranking.clear();
                        ranking.display();
                        }
                    }
                    if (x == 2)
                        menu_window.close();
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
                        while (ranking.isOpen())
                        {
                            sf::Event event2;
                            while (ranking.pollEvent(event2))
                            {
                                if (event2.type == sf::Event::Closed)
                                    ranking.close();
                            }
                        menu_window.close(); 
                        window.close();
                        ranking.clear();
                        ranking.display();
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


