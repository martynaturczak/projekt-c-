#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "map.h"

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Game");
    sf::View view(sf::Vector2f(256.f, 128.f), sf::Vector2f(512.f, 256.f));
    sf::Vector2f position;
    sf::Clock clock;
    const float timestep = 1.0/60.0;
    float time = 0;
    
    sf::Texture texture;
	texture.loadFromFile("player.png");
    sf::Sprite sprite;
	sprite.setTexture(texture);
    position.x = 10;
    position.y = 192;
    sprite.setPosition(position.x,position.y);
    
    float velocityX = 0, velocityY = 0;
    float accelerationX = 0, accelerationY = 0;
    float gravity = 0.05;
    bool on_ground = 1;

    const int level[] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    TileMap map;
    if (!map.load("set.png", sf::Vector2u(32, 32), level, 32, 8))
        return -1;

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
            //kolizje
            if (level[(int)(position.y/32)*32 + (int)((position.x + 32 + velocityX)/32)] == 2)
            {
                velocityX = 0;
            }
            if (level[(int)((position.y + 32)/32)*32 + (int)((position.x + 32 + velocityX)/32)] == 2)
            {
                velocityX = 0;
            }
            if (level[(int)(position.y/32)*32 + (int)((position.x + velocityX)/32)] == 2)
            {
                velocityX = 0;
            }
            if (level[(int)((position.y + 32)/32)*32 + (int)((position.x + velocityX)/32)] == 2)
            {
                velocityX = 0;
            }
            if ((level[(int)((position.y + 32 + velocityY)/32)*32 + (int)((position.x + 32)/32)] == 2) or (level[(int)((position.y + 32 + velocityY)/32)*32 + (int)((position.x + 32)/32)] == 0))
            {
                velocityY = 0;
                on_ground = 1;
            }
            if (level[(int)((position.y + 32 + velocityY)/32)*32 + (int)(position.x/32)] == 2 or (level[(int)((position.y + 32 + velocityY)/32)*32 + (int)((position.x)/32)] == 0))
            {
                velocityY = 0;
                on_ground = 1; 
            }
            // if ((level[(int)((position.y - 32 + velocityY)/32)*32 + (int)((position.x + 32)/32)] == 3))
            // {
            //     velocityY = 0;
            // }
            // if (level[(int)((position.y - 32 + velocityY)/32)*32 + (int)(position.x/32)] == 3)
            // {
            //     velocityY = 0;
            // }
            position.x += velocityX;
            position.y += velocityY;

        
            view.move(velocityX, 0);
        }
        
        window.clear();
        window.setView(view);
        sprite.setPosition(position.x, position.y);
        window.draw(map);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
